`std::cerr` 和 `std::clog` 是 C++ 标准库中用于**输出错误 / 日志信息**的流对象（定义在 `<iostream>` 头文件中）

1.`std::cout`和`std::cerr`和`std::clog`的不同

| 特性             | `std::cout`（标准输出）       | `std::cerr`（标准错误输出）   | `std::clog`（日志输出） |
| ---------------- | ----------------------------- | ----------------------------- | ----------------------- |
| 绑定的系统流     | `stdout`（标准输出）          | `stderr`（标准错误）          | `stderr`（标准错误）    |
| 缓冲策略         | 全缓冲（默认）                | 无缓冲（立即输出）            | 行缓冲（按行输出）      |
| 输出目标（默认） | 终端 / 控制台                 | 终端 / 控制台                 | 终端 / 控制台           |
| 重定向行为       | 可被重定向（如 `> file.txt`） | 可被重定向（如 `2> err.log`） | 同 cerr（绑定 stderr）  |
| 核心用途         | 正常程序输出（结果 / 提示）   | 紧急错误信息（立即显示）      | 程序日志 / 非紧急错误   |

**std::cout（全缓冲）**：默认会把输出内容暂存到缓冲区，直到缓冲区满 / 程序结束 / 手动刷新（`std::flush`/`std::endl`）才输出。

优点：减少 I/O 调用，效率高；缺点：紧急信息可能延迟显示。

**std::cerr（无缓冲）**：

写入的内容**立即输出**到目标，不经过任何缓冲区。

优点：错误信息实时显示，即使程序崩溃也能看到关键错误；缺点：频繁输出时效率略低。

**std::clog（行缓冲）**：

按「行」缓冲 —— 遇到换行符（`\n`/`std::endl`）时立即输出，否则暂存。

```c++
#include <iostream>
#include <unistd.h> // sleep函数（Linux/macOS），Windows用Sleep（大写S）
using namespace std;

int main() {
    cout << "cout输出（无换行）"; // 全缓冲，暂存不输出
    cerr << "cerr输出（无换行）"; // 无缓冲，立即输出
    clog << "clog输出（无换行）"; // 行缓冲，暂存不输出

    sleep(3); // 暂停3秒，观察输出时机
    cout << "\ncout换行后输出" << endl; // 换行+刷新，输出之前的内容
    clog << "\nclog换行后输出" << endl; // 换行，输出之前的内容

    return 0;
}

```

2.使用场景

#### 1. std::cerr：紧急 / 致命错误

用于输出程序运行中**必须立即关注**的错误，比如参数错误、文件打开失败、内存分配失败等：

```c++
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("test.txt");
    if (!file.is_open()) {
        // 错误信息立即输出，不缓冲
        cerr << "致命错误：无法打开文件 test.txt！" << endl;
        return 1; // 异常退出
    }
    // 正常逻辑...
    return 0;
}

```

#### 2. std::clog：程序日志 / 非紧急提示

用于输出程序运行过程中的「状态日志」「非致命警告」，比如初始化完成、处理进度、次要警告等：

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {1,2,3};
    clog << "日志：程序启动，初始化vector大小为 " << vec.size() << endl;

    if (vec.size() < 5) {
        clog << "警告：vector大小小于5，可能影响后续处理" << endl;
    }

    // 正常逻辑...
    clog << "日志：程序处理完成，退出" << endl;
    return 0;
}

```

#### 3. std::cout：正常业务输出

用于输出程序的「预期结果」「用户提示」等非错误类内容：

```c++
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    cout << "计算结果：a + b = " << (a + b) << endl;
    cout << "请输入一个整数："; // 提示用户输入
    int x;
    cin >> x;
    cout << "你输入的数是：" << x << endl;
    return 0;
}

```

不要用 `cout` 输出错误信息（可能因缓冲延迟导致错误信息丢失），也不要用 `cerr` 输出正常结果（会干扰错误日志的分离）。

- 「用户需要看的正常结果」用 `cout`；
- 「程序员需要排查的错误」用 `cerr`（紧急）/`clog`（日志）；
- 重定向时，`cout` 走 `stdout`，`cerr/clog` 走 `stderr`，便于分离日志。