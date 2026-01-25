#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <cerrno>
#include <charconv>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <vector>

// 颜色常量（改用constexpr字符串替代宏，更符合C++类型安全）
constexpr std::string_view BLUE = "\033[1;34m";
constexpr std::string_view GREEN = "\033[1;32m";
constexpr std::string_view YELLOW = "\033[1;33m";
constexpr std::string_view CYAN = "\033[1;36m";
constexpr std::string_view MAGENTA = "\033[1;35m";
constexpr std::string_view RESET = "\033[0m";
constexpr std::string_view RED = "\033[1;31m";

// 常量定义
constexpr int PATH_MAX = 4096;
constexpr int BLOCK_SIZE = 512;

// 全局配置（封装为结构体，替代全局变量）
struct LsConfig {
    bool flag_a = false;      // 显示隐藏文件
    bool flag_R = false;      // 递归遍历
    bool flag_r = false;      // 逆序排序
    bool flag_t = false;      // 按时间排序
    bool flag_i = false;      // 显示inode
    bool flag_s = false;      // 显示块大小
    bool flag_l = false;      // 长格式显示
    std::string current_dir;  // 当前遍历的目录
} config;

// 初始化本地化设置
void init_locale() {
    std::locale::global(std::locale(""));
    setlocale(LC_COLLATE, "");
    setlocale(LC_CTYPE, "");
}

// 后缀-颜色映射表（改用unordered_map，O(1)查找效率更高）
const std::unordered_map<std::string, std::string_view> SUFFIX_COLOR_MAP = {
    {"gz", RED},
    {"xz", RED},
    {"zip", RED},
    {"jpg", MAGENTA},
    {"png", MAGENTA}};

// 判断文件后缀并返回对应颜色
std::string_view get_suffix_color(const std::string& filename) {
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos == std::string::npos)
        return "";

    std::string suffix = filename.substr(dot_pos + 1);
    // 忽略大小写转换
    std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);

    auto it = SUFFIX_COLOR_MAP.find(suffix);
    return (it != SUFFIX_COLOR_MAP.end()) ? it->second : "";
}

// 字符类型枚举
enum class CharType { ENGLISH = 0, SYMBOL = 1, CHINESE = 2, NUMBER = 3 };

// 判断字符类型
CharType get_char_type(unsigned char c, bool is_chinese = false) {
    if (is_chinese)
        return CharType::CHINESE;
    if (c >= '0' && c <= '9')
        return CharType::NUMBER;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return CharType::ENGLISH;
    return CharType::SYMBOL;
}

// 获取文件名优先级（用于排序）
int get_priority(const std::string& name) {
    std::string temp = name;
    // 跳过开头的点
    size_t pos = temp.find_first_not_of('.');
    if (pos == std::string::npos)
        return -1;  // 全是点的文件
    temp = temp.substr(pos);

    unsigned char first_byte = static_cast<unsigned char>(temp[0]);
    bool is_chinese = (first_byte >= 0xE0 && first_byte <= 0xEF);
    CharType type = get_char_type(first_byte, is_chinese);

    switch (type) {
        case CharType::CHINESE:
            return 2;
        case CharType::NUMBER:
            return 3;
        case CharType::ENGLISH:
            return 0;
        case CharType::SYMBOL:
            return 1;
        default:
            return 1;
    }
}

// 过滤函数（scandir的回调）
int filter(const struct dirent* entry) {
    return config.flag_a ? 1 : (entry->d_name[0] != '.');
}

// 文件信息结构体（封装dirent和stat）
struct FileInfo {
    std::string name;
    std::string full_path;
    struct dirent dir_ent;
    struct stat file_stat;

    // 构造函数
    FileInfo(const std::string& dir, const struct dirent* ent)
        : name(ent->d_name), dir_ent(*ent) {
        // 拼接完整路径（C++风格）
        full_path =
            (dir.empty() || dir.back() == '/') ? dir + name : dir + "/" + name;
        // 获取文件属性
        if (lstat(full_path.c_str(), &file_stat) == -1) {
            throw std::system_error(errno, std::generic_category(),
                                    "lstat failed: " + full_path);
        }
    }
};

// 按名称排序的比较函数
bool compare_by_name(const FileInfo& a, const FileInfo& b) {
    // 优先处理.和..
    if (a.name == ".")
        return true;
    if (b.name == ".")
        return false;
    if (a.name == "..")
        return true;
    if (b.name == "..")
        return false;

    int pri_a = get_priority(a.name);
    int pri_b = get_priority(b.name);
    if (pri_a != pri_b) {
        return config.flag_r ? (pri_a < pri_b) : (pri_a > pri_b);
    }

    switch (static_cast<CharType>(pri_a)) {
        case CharType::NUMBER: {
            long num_a = std::atol(a.name.c_str());
            long num_b = std::atol(b.name.c_str());
            return config.flag_r ? (num_a > num_b) : (num_a < num_b);
        }
        case CharType::CHINESE: {
            return config.flag_r
                       ? (strcoll(a.name.c_str(), b.name.c_str()) > 0)
                       : (strcoll(a.name.c_str(), b.name.c_str()) < 0);
        }
        case CharType::SYMBOL: {
            return config.flag_r ? (a.name > b.name) : (a.name < b.name);
        }
        case CharType::ENGLISH: {
            std::string a_lower = a.name;
            std::string b_lower = b.name;
            std::transform(a_lower.begin(), a_lower.end(), a_lower.begin(),
                           ::tolower);
            std::transform(b_lower.begin(), b_lower.end(), b_lower.begin(),
                           ::tolower);
            return config.flag_r ? (a_lower > b_lower) : (a_lower < b_lower);
        }
        default:
            return config.flag_r ? (a.name > b.name) : (a.name < b.name);
    }
}

// 按时间排序的比较函数
bool compare_by_time(const FileInfo& a, const FileInfo& b) {
    long time_a = a.file_stat.st_mtime;
    long time_b = b.file_stat.st_mtime;
    return config.flag_r ? (time_a < time_b) : (time_a > time_b);
}

// 打印权限字符串
std::string get_permission_string(const struct stat& st) {
    std::string perm;
    // 文件类型
    if (S_ISDIR(st.st_mode))
        perm += 'd';
    else if (S_ISLNK(st.st_mode))
        perm += 'l';
    else if (S_ISCHR(st.st_mode))
        perm += 'c';
    else if (S_ISBLK(st.st_mode))
        perm += 'b';
    else if (S_ISFIFO(st.st_mode))
        perm += 'p';
    else if (S_ISSOCK(st.st_mode))
        perm += 's';
    else
        perm += '-';

    // 所有者权限
    perm += (st.st_mode & S_IRUSR) ? 'r' : '-';
    perm += (st.st_mode & S_IWUSR) ? 'w' : '-';
    if (st.st_mode & S_ISUID) {
        perm += (st.st_mode & S_IXUSR) ? 's' : 'S';
    } else {
        perm += (st.st_mode & S_IXUSR) ? 'x' : '-';
    }

    // 组权限
    perm += (st.st_mode & S_IRGRP) ? 'r' : '-';
    perm += (st.st_mode & S_IWGRP) ? 'w' : '-';
    if (st.st_mode & S_ISGID) {
        perm += (st.st_mode & S_IXGRP) ? 's' : 'S';
    } else {
        perm += (st.st_mode & S_IXGRP) ? 'x' : '-';
    }

    // 其他用户权限
    perm += (st.st_mode & S_IROTH) ? 'r' : '-';
    perm += (st.st_mode & S_IWOTH) ? 'w' : '-';
    perm += (st.st_mode & S_IXOTH) ? 'x' : '-';

    return perm;
}

// 获取用户名称
std::string get_username(uid_t uid) {
    struct passwd* pw = getpwuid(uid);
    if (pw)
        return pw->pw_name;
    return std::to_string(uid);
}

// 获取组名称
std::string get_groupname(gid_t gid) {
    struct group* gr = getgrgid(gid);
    if (gr)
        return gr->gr_name;
    return std::to_string(gid);
}

// 获取格式化时间字符串
std::string get_time_string(time_t mtime) {
    struct tm* tm = localtime(&mtime);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%m月 %d %H:%M", tm);
    return std::string(time_str);
}

// 打印文件信息（纯C++风格，使用cout）
void print_file_info(const FileInfo& file) {
    const auto& st = file.file_stat;
    const auto& name = file.name;
    const auto& full_path = file.full_path;
    std::ostream& os = std::cout;

    // 显示inode
    if (config.flag_i) {
        os << std::setw(8) << std::right << st.st_ino << " ";
    }

    // 显示块大小
    if (config.flag_s) {
        long block_size = (st.st_blocks * BLOCK_SIZE) / 1024;
        os << std::setw(5) << std::right << block_size << " ";
    }

    // 长格式显示（-l参数）
    if (config.flag_l) {
        // 权限字符串
        os << get_permission_string(st) << "    ";
        // 链接数
        os << std::setw(3) << std::right << st.st_nlink << "    ";
        // 所有者
        os << std::setw(8) << std::left << get_username(st.st_uid) << "    ";
        // 所属组
        os << std::setw(8) << std::right << get_groupname(st.st_gid) << " ";
        // 文件大小
        os << std::setw(8) << std::right << st.st_size << " ";
        // 修改时间
        os << get_time_string(st.st_mtime) << " ";
    }

    // 设置颜色
    if (S_ISDIR(st.st_mode)) {
        os << BLUE;
    } else if (S_ISLNK(st.st_mode)) {
        os << CYAN;
    } else if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) {
        os << YELLOW;
    } else if (S_ISFIFO(st.st_mode)) {
        os << YELLOW;
    } else if (S_ISSOCK(st.st_mode)) {
        os << MAGENTA;
    } else {
        // 按后缀设置颜色
        auto suffix_color = get_suffix_color(name);
        if (!suffix_color.empty()) {
            os << suffix_color;
        } else if ((st.st_mode & (S_ISUID | S_ISGID)) &&
                   !(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
            os << RED;
        } else if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            os << GREEN;
        }
    }

    // 输出文件名（处理符号链接）
    if (config.flag_l && S_ISLNK(st.st_mode)) {
        char link_path[PATH_MAX];
        ssize_t len = readlink(full_path.c_str(), link_path, PATH_MAX - 1);
        if (len != -1) {
            link_path[len] = '\0';
            os << name << "->" << link_path << "\n";
        } else {
            os << name << "\n";
        }
    } else {
        os << name << "\n";
    }

    // 重置颜色
    os << RESET;

    // 刷新输出
    os.flush();
}

// 遍历目录（核心逻辑）
void list_dir(const std::string& dir) {
    // 递归模式下打印目录名
    if (config.flag_R) {
        std::cout << dir << ":\n";
    }

    // 扫描目录
    struct dirent** entries = nullptr;
    int count = scandir(dir.c_str(), &entries, filter, nullptr);
    if (count == -1) {
        std::cerr << "scandir failed: " << dir << " - " << std::strerror(errno)
                  << "\n";
        return;
    }

    // 封装文件信息到vector
    std::vector<FileInfo> file_list;
    try {
        for (int i = 0; i < count; ++i) {
            if (entries[i]) {
                file_list.emplace_back(dir, entries[i]);
                free(entries[i]);  // 释放scandir分配的内存
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing file: " << e.what() << "\n";
    }
    free(entries);

    // 排序
    if (config.flag_t) {
        std::sort(file_list.begin(), file_list.end(), compare_by_time);
    } else {
        std::sort(file_list.begin(), file_list.end(), compare_by_name);
    }

    // 存储递归目录
    std::vector<std::string> sub_dirs;

    // 打印文件信息
    for (const auto& file : file_list) {
        try {
            print_file_info(file);

            // 收集递归目录
            if (config.flag_R && !S_ISLNK(file.file_stat.st_mode) &&
                S_ISDIR(file.file_stat.st_mode) && file.name != "." &&
                file.name != "..") {
                sub_dirs.push_back(file.full_path);
            }
        } catch (const std::exception& e) {
            std::cerr << "Failed to print file " << file.name << ": "
                      << e.what() << "\n";
        }
    }

    // 非长格式时打印空行分隔
    if (!config.flag_l) {
        std::cout << "\n";
    }

    // 递归遍历子目录
    for (const auto& sub_dir : sub_dirs) {
        list_dir(sub_dir);
    }
}

int main(int argc, char* argv[]) {
    try {
        init_locale();

        // 解析命令行参数
        int opt;
        while ((opt = getopt(argc, argv, "laRtris")) != -1) {
            switch (opt) {
                case 'a':
                    config.flag_a = true;
                    break;
                case 'l':
                    config.flag_l = true;
                    break;
                case 'R':
                    config.flag_R = true;
                    break;
                case 's':
                    config.flag_s = true;
                    break;
                case 'i':
                    config.flag_i = true;
                    break;
                case 't':
                    config.flag_t = true;
                    break;
                case 'r':
                    config.flag_r = true;
                    break;
                case '?':
                    std::cerr << "ls: 参数无效：'" << static_cast<char>(optopt)
                              << "'\n";
                    return EXIT_FAILURE;
                default:
                    return EXIT_FAILURE;
            }
        }

        // 收集要遍历的目录/文件
        std::vector<std::string> targets;
        if (optind >= argc) {
            targets.emplace_back(".");  // 默认当前目录
        } else {
            for (int i = optind; i < argc; ++i) {
                targets.emplace_back(argv[i]);
            }
        }

        // 处理每个目标
        for (const auto& target : targets) {
            struct stat st;
            if (stat(target.c_str(), &st) == -1) {
                std::cerr << target << ": " << std::strerror(errno) << "\n";
                continue;
            }

            if (S_ISDIR(st.st_mode)) {
                // 遍历目录
                list_dir(target);
            } else {
                // 处理单个文件
                struct dirent ent = {0};
                std::strncpy(ent.d_name, target.c_str(),
                             sizeof(ent.d_name) - 1);
                ent.d_name[sizeof(ent.d_name) - 1] = '\0';

                try {
                    FileInfo file("", &ent);
                    print_file_info(file);
                    if (!config.flag_l) {
                        std::cout << "\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error processing file " << target << ": "
                              << e.what() << "\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
