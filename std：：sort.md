`std::sort`

用头文件`<algorithm`

1.示例

```c++
#include <algorithm>
#include <vector>
#include <iostream>
int main() {
    std::vector<int> nums = {5, 2, 8, 1, 9, 3};
    // 1. 默认升序排序
    std::sort(nums.begin(), nums.end());
    // 2. 降序排序
    std::sort(nums.begin(), nums.end(), std::greater<int>()); // 用到<algorithm>头文件
    return 0;
}

```

2.`std::greater<int>()`

`std::greater` 是一个模板类，针对 `int` 类型的特化版逻辑如下,不是普通函数，而是类实例，但可通过 `operator()` 像函数一样调用

```c++
template <typename T>
struct greater {
    // 重载()运算符，比较两个T类型值
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};
//举个例子：
#include <iostream>
#include <functional> // 必须包含此头文件
using namespace std;

int main() {
    // 创建greater<int>对象并调用
    greater<int> comp;
    bool res1 = comp(5, 3);  // 5 > 3 → true
    bool res2 = comp(3, 5);  // 3 > 5 → false

    // 更常用：直接创建临时对象并调用
    bool res3 = greater<int>()(10, 7); // 10 > 7 → true

    cout << res1 << " " << res2 << " " << res3 << endl; // 输出 1 0 1
    return 0;
}

```

使用场景：

`std::sort`默认实现升序排序，`std::greater<int>`可改为降序

3.为什么不用普通函数或 Lambda 替代？三者对比：

| 方式                | 示例                                                         | 优点                           | 缺点                                       |
| ------------------- | ------------------------------------------------------------ | ------------------------------ | ------------------------------------------ |
| std::greater<int>() | `sort(v.begin(), v.end(), greater<int>())`                   | 标准库内置，无需手写，可读性高 | 仅支持简单的 `a > b` 比较                  |
| 普通函数            | `bool comp(int a, int b) { return a > b; }`                  | 逻辑可自定义                   | 无法内联（可能有函数调用开销）、模板适配差 |
| Lambda 表达式       | `sort(v.begin(), v.end(), [](int a, int b){ return a > b; })` | 灵活（可加复杂逻辑）、可内联   | 简单比较时略显冗余                         |



4.和qsort的核心差异

| 特性               | `std::sort`（C++）                                           | `qsort`（C）                                     |
| ------------------ | ------------------------------------------------------------ | ------------------------------------------------ |
| **类型安全**       | 强类型（模板化），编译期检查类型匹配                         | 无类型（void* 泛型），编译期无类型检查           |
| **比较函数**       | 直接比较具体类型（如 `int a, int b`），返回 bool             | 比较 void* 指针，返回 int（<0/0/>0），需手动强转 |
| **性能**           | 更快（编译期内联比较函数，无函数调用开销）                   | 较慢（运行时函数指针调用，强转有额外开销）       |
| **底层实现**       | 混合排序（通常是 IntroSort：快速排序 + 堆排序 + 插入排序），平均 / 最坏 O (n logn) | 快速排序（不同实现略有差异），最坏 O (n²)        |
| **支持的排序范围** | 随机访问迭代器（vector/array/deque 等）                      | 任意连续内存（数组），需指定元素大小             |
| **异常安全**       | 支持（比较函数抛异常会终止程序，但符合 C++ 异常模型）        | 无异常概念（C 无异常）                           |
| **可定制性**       | 支持自定义比较函数 / 函数对象 /λ 表达式，语法简洁            | 仅支持函数指针，语法繁琐                         |
| **返回值**         | 无返回值（直接修改容器 / 数组）                              | 无返回值（直接修改数组）                         |

5.容器自带排序方法

`std::list`和`std::forward_list`

```c++
#include <list>

std::list<int> lst = {5, 2, 8, 1, 9, 3};

// list有自己的sort方法（因为std::sort需要随机访问迭代器）
lst.sort();  // 升序
lst.sort(std::greater<int>());  // 降序

```





