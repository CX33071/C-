`STL`初识

- STL(Standard Template Library,**标准模板库**)
- STL 从广义上分为: **容器(container) 算法(algorithm) 迭代器(iterator)**
- **容器**和**算法**之间通过**迭代器**进行无缝连接。
- STL 几乎所有的代码都采用了模板类或者模板函数

STL大体分为六大组件，分别是:**容器、算法、迭代器、仿函数、适配器（配接器）、空间配置器**

1. 容器：各种数据结构，如vector、list、deque、set、map等,用来存放数据。

2. 算法：各种常用的算法，如sort、find、copy、for_each等

3. 迭代器：扮演了容器与算法之间的胶合剂。

4. 仿函数：行为类似函数，可作为算法的某种策略。

5. 适配器：一种用来修饰容器或者仿函数或迭代器接口的东西。

6. 空间配置器：负责空间的配置与管理。

   STL**容器**就是将运用**最广泛的一些数据结构**实现出来

   常用的数据结构：数组, 链表,树, 栈, 队列, 集合, 映射表 等

   这些容器分为**序列式容器**和**关联式容器**两种:

   ​	**序列式容器**:强调值的排序，序列式容器中的每个元素均有固定的位置。 **关联式容器**:二叉树结构，各元素之间没有严格的物理上的顺序关系

   **算法：**问题之解法也

   有限的步骤，解决逻辑或数学上的问题，这一门学科我们叫做算法(Algorithms)

   算法分为:**质变算法**和**非质变算法**。

   质变算法：是指运算过程中会更改区间内的元素的内容。例如拷贝，替换，删除等等

   非质变算法：是指运算过程中不会更改区间内的元素内容，例如查找、计数、遍历、寻找极值等等

   **迭代器：**容器和算法之间粘合剂

   提供一种方法，使之能够依序寻访某个容器所含的各个元素，而又无需暴露该容器的内部表示方式。

   每个容器都有自己专属的迭代器

   迭代器使用非常类似于指针，初学阶段我们可以先理解迭代器为指针

**首先了解什么是类模板？**

允许你定义一个 “通用的类模板”，而非具体的类 —— 通过指定不同的**模板参数**（如类型、常量），编译器会自动生成适配该参数的具体类，是 STL 容器（如 `vector<int>`、`map<string, int>`）的底层实现基础

语法：

```c++
// 模板参数列表：template <参数类型1, 参数类型2, ...>
template <typename T, typename U = int> // T/U 是类型参数，U 有默认值
class 模板类名 {
    // 类成员：可使用模板参数 T/U
    T data1;
    U data2;
public:
    // 成员函数：可使用模板参数
    void setData(const T& d1, const U& d2) {
        data1 = d1;
        data2 = d2;
    }
    T getData1() const { return data1; }
};

```

`std::vector` 是 **类模板**，而非普通的类 —— 可以把它理解为「生成具体容器类的 “模板”」，通过指定模板参数（如元素类型），就能实例化出具体的 `vector` 类

1.`vector`类模板定义

```c++
namespace std {
    // 类模板定义：T 是元素类型，Allocator 是内存分配器（默认 std::allocator<T>）
    template <typename T, typename Allocator = std::allocator<T>>
    class vector {
        // 成员变量（如动态数组指针、size、capacity）
        T* _data;
        size_t _size;
        size_t _capacity;
    public:
        // 成员函数（如 push_back、pop_back、insert、erase 等）
        void push_back(const T& value);
        void pop_back();
        T& operator[](size_t idx);
        // ... 其他成员
    };
}

```

`T` 是 “类型占位符”，表示容器存储的元素类型；

**实例化**：当你写 `std::vector<int>`、`std::vector<std::string>` 时，编译器会根据模板参数 `T`（`int`/`std::string`），生成**具体的类**—— 这才是你实际使用的 `vector` 类

普通类的成员类型是固定的（比如一个 `IntArray` 类只能存 `int`），但 `vector` 需要支持存储任意类型（`int`、`string`、自定义类等），类模板正是为了解决「一套逻辑适配多种类型」的问题

实例化后的`vector`是类：

成员变量：存储数据的动态数组指针、size(元素个数）、capacity（容量）

成员函数：push_back()、pop_back()、size()、capacity()

```c++
std::cout<<vec1.size()<<vec1.capacity();//这两个函数是vector的成员函数
```

支持创建对象：`std::vector<int>vec;`

2.特性

| 特性       | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| 内存布局   | 连续的内存块（与原生数组一致），支持随机访问（O (1)）        |
| 扩容机制   | 容量不足时，自动分配**2 倍** 新内存，拷贝原元素后释放旧内存  |
| 增删效率   | 尾部增删 O (1)（均摊），中间 / 头部增删 O (n)（需移动后续元素） |
| 大小与容量 | `size()`：已存储元素个数；`capacity()`：已分配内存可容纳的元素个数 |
| 迭代器     | 随机访问迭代器（支持 `[]`、`+`、`-` 等操作），扩容后迭代器失效 |

3.头文件与初始化

```c++
#include <vector>   // 必须包含头文件
#include <iostream>
using namespace std;

int main() {
    // 方式1：空vector
    vector<int> vec1;

    // 方式2：指定大小，默认初始化（int为0，自定义类型调用默认构造）
    vector<int> vec2(5);       // {0,0,0,0,0}

    // 方式3：指定大小+初始值
    vector<int> vec3(5, 10);   // {10,10,10,10,10}

    // 方式4：列表初始化（C++11+）
    vector<int> vec4 = {1,2,3,4,5};

    // 方式5：拷贝初始化
    vector<int> vec5(vec4);    // 拷贝vec4的所有元素
//和 push_back 逐个添加元素不同，拷贝构造会一次性分配足够的内存（直接匹配原 vector 的容量），不会出现「先分配小内存→元素拷贝→容量不足→扩容→再拷贝」的低效行为，直接读取vec4的size()和capacity()
    // 方式6：范围初始化（迭代器）
    vector<int> vec6(vec4.begin()+1, vec4.end()-1); // {2,3,4}

    return 0;
}

```

4.核心操作

| 操作                                                         | 代码示例                        | 说明                                                         |
| ------------------------------------------------------------ | ------------------------------- | ------------------------------------------------------------ |
| 尾部添加                                                     | `vec.push_back(6);`             | 尾部插入元素，容量不足时触发扩容                             |
| 尾部删除                                                     | `vec.pop_back();`               | 删除尾部元素，仅修改 size，不释放内存，capacity()不变        |
| 随机访问                                                     | `vec[2];` / `vec.at(2);`        | `[]` 无越界检查（快）；`at()` 有越界检查（抛 `out_of_range` 异常） |
| 插入元素                                                     | `vec.insert(vec.begin()+1, 9);` | 在指定位置插入元素，后续元素后移，O (n) 时间                 |
| 删除元素                                                     | `vec.erase(vec.begin()+1);`     | 删除指定位置元素，后续元素前移，O (n) 时间                   |
| 清空元素                                                     | `vec.clear();`                  | 清空所有元素（size=0，capacity 不变）                        |
| 调整大小                                                     | `vec.resize(8);`                | 若新 size > 旧 size，补默认值；若新 size < 旧 size，截断尾部元素 |
| 预分配容量                                                   | `vec.reserve(20);`              | 预分配容量（仅改变 capacity，不改变 size），避免频繁扩容     |
| 释放多余内存                                                 | `vector<int>(vec).swap(vec);`   | 收缩 capacity 到等于 size（C++11 后可直接用 `shrink_to_fit()`） |
| **在 vector 尾部 “就地构造” 元素**，相比传统的 `push_back()` 更高效（避免临时对象的拷贝 / 移动） | vec.emplace_back();             | 就地构造（直接在 vector 内存中创建）                         |
| 获取vector底层存储数组的首地址                               | cmd_argv.data()                 |                                                              |

```c++
int main() {
    vector<int> vec = {1,2,3};

    // 尾部操作
    vec.push_back(4);       // {1,2,3,4}
    vec.pop_back();         // {1,2,3}

    // 插入/删除
    auto it = vec.insert(vec.begin()+1, 9); // 插入9到索引1，返回新元素迭代器
    cout << *it << endl;    // 输出9，此时vec={1,9,2,3}

    vec.erase(vec.begin()+1); // 删除索引1的元素，vec={1,2,3}

    // 访问
    cout << vec[1] << endl; // 2（无越界检查）
    cout << vec.at(1) << endl; // 2（有越界检查）

    // 容量管理
    cout << "size: " << vec.size() << endl; // 3
    cout << "capacity: " << vec.capacity() << endl; // 3（初始容量等于size）

    vec.reserve(10); // 预分配容量到10
    cout << "capacity after reserve: " << vec.capacity() << endl; // 10

    vec.clear(); // 清空元素，size=0，capacity仍为10
    cout << "size after clear: " << vec.size() << endl; // 0

    // 收缩容量
    vector<int>(vec).swap(vec);
    cout << "capacity after shrink: " << vec.capacity() << endl; // 0

    return 0;
}

```

5.优化

(1)`reserve` 可提前预留足够容量，避免多次扩容：

```c++
// 反例：循环push_back，频繁扩容
vector<int> bad_vec;
for (int i = 0; i < 1000000; ++i) {
    bad_vec.push_back(i); // 多次扩容，性能差
}

// 正例：提前reserve，仅1次分配
vector<int> good_vec;
good_vec.reserve(1000000); // 预分配100万容量
for (int i = 0; i < 1000000; ++i) {
    good_vec.push_back(i); // 无扩容，性能提升显著
}
```

(2)使用 emplace_back 替代 push_back

`push_back` 会先构造临时对象，再拷贝 / 移动到容器；`emplace_back` 直接在容器尾部**就地构造**对象，避免临时对象的拷贝：

```c++
// 自定义类型示例
struct Person {
    string name;
    int age;
    Person(string n, int a) : name(n), age(a) {} // 带参构造
};

int main() {
    vector<Person> vec;
    vec.reserve(100);

    // push_back：先构造临时Person，再移动到vec
    vec.push_back(Person("Alice", 20));

    // emplace_back：直接在vec尾部构造Person，无临时对象
    vec.emplace_back("Bob", 21);

    return 0;
}

```

