`constexpr`

1.`constexpr`和`const`的区别

`constexpr`强调编译期就确定，`const`初始值在运行时才确定

| 本质区别 | const        | constexpr    |
| -------- | ------------ | ------------ |
| 确定时机 | 运行时初始化 | 编译期初始化 |
| 内存占用 | 占用内存     | 不占用内存   |

```c++
#include <iostream>
using namespace std;

int get_runtime_val() { return 10; } // 运行时函数

int main() {
    // ===== const 示例 =====
    const int a = 10;          // 编译期初始化（只读）
    const int b = get_runtime_val(); // 运行时初始化（只读，合法）
    // int arr_b[b];           // 错误！b 是运行时常量，不能作为数组大小（C++标准，部分编译器扩展支持）
    
    // ===== constexpr 示例 =====
    constexpr int c = 10;      // 编译期常量（合法）
    // constexpr int d = get_runtime_val(); // 错误！get_runtime_val() 是运行时函数，无法编译期求值
    int arr_c[c];              // 合法！c 是编译期常量，可用于数组大小
    
    return 0;
}

```

注意点

```c++
#include <iostream>
using namespace std;

int get_runtime_val() { return 10; } // 运行时函数

int main() {
    // ===== const 示例 =====
    const int a = 10;          // 编译期初始化（只读）
    const int b = get_runtime_val(); // 运行时初始化（只读，合法）
    // int arr_b[b];           // 错误！b 是运行时常量，不能作为数组大小（C++标准，部分编译器扩展支持）
    
    // ===== constexpr 示例 =====
    constexpr int c = 10;      // 编译期常量（合法）
    // constexpr int d = get_runtime_val(); // 错误！get_runtime_val() 是运行时函数，无法编译期求值
    int arr_c[c];              // 合法！c 是编译期常量，可用于数组大小
    
    return 0;
}
```

2.宏定义和`constexpr`常量

| 特性           | 宏定义（#define）                      | constexpr 常量                    |
| -------------- | -------------------------------------- | --------------------------------- |
| **类型检查**   | 无类型（纯文本替换），编译器不检查类型 | 强类型（int），编译期严格类型校验 |
| **编译期计算** | 文本替换，无 “计算” 概念               | 编译期求值，可参与编译期表达式    |
| **语法安全**   | 易因文本替换引发语法错误（如括号缺失） | 语法和普通变量一致，无替换陷阱    |

宏定义是**预处理器文本替换**，无类型概念，可能导致隐式类型错误：

```c++
// 宏定义的问题：纯文本替换，无类型检查
#define PATH_MAX 4096
char buf[PATH_MAX + 0.5]; // 预处理器替换为 char buf[4096 + 0.5]; 编译报错，但错误信息不直观
#define BLOCK_SIZE "512"   // 手滑写错成字符串，编译器不会提前发现

// constexpr 常量：强类型，编译期直接报错
constexpr int PATH_MAX = 4096;
char buf[PATH_MAX + 0.5]; // 编译期提示：不能将 double 转换为 int，错误信息清晰
constexpr int BLOCK_SIZE = 512; // 类型是 int，若误写为字符串会直接编译失败

```

`constexpr`能提前规避这些问题，要注意的是`constexpr`无法直接代替字符串字面量宏，要通过`constexpr const char*`替代

