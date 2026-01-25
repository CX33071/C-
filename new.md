new动态分配内存大小

1.优点：自动计算内存大小（无需`sizeof`)

​		直接返回对应类型指针，无需强制类型转换

​		支持初始化`new int(10)`

2.动态分配单个变量

**类型*指针变量=new 类型 (初始值)；**

**类型*指针变量=new类型；**（初始化值随机）

```c
#include <iostream>
using namespace std;

int main() {
    // 1. 动态分配单个 int 变量（默认初始化，值随机）
    int* p1 = new int;
    cout << "默认初始化：" << *p1 << endl;  // 输出随机值（堆内存未清零）
    
    // 2. 动态分配并显式初始化（推荐）
    int* p2 = new int(100);  // 分配 int 大小的堆内存，赋值为 100
    cout << "显式初始化：" << *p2 << endl;  // 输出 100
    
    // 3. 动态分配其他类型（double、char 等）
    double* p3 = new double(3.14);
    char* p4 = new char('A');
    cout << "double：" << *p3 << ", char：" << *p4 << endl;  // 3.14, A
    
    // 关键：动态分配的内存必须手动释放（用 delete），否则内存泄漏！
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    
    return 0;
}

```

```c
delete p2;
p2 = nullptr;  // 标记指针为空，后续可通过 if(p2 != nullptr) 判断

```

3.动态分配数组

new支持用变量作为数组长度

**类型*指针变量=new类型[数组长度]；**

**类型*指针变量=new类型[数组长度]();**,初始化为0

```c
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "请输入数组长度：";
    cin >> n;  // 运行时输入长度（C语言数组做不到）
    
    // 1. 动态分配数组（默认初始化，int 元素值随机）
    int* arr1 = new int[n];
    // 2. 动态分配数组并值初始化（所有元素置0，C++11+支持）
    int* arr2 = new int[n]();  // 括号 () 表示值初始化
    
    // 赋值并输出
    for (int i = 0; i < n; i++) {
        arr1[i] = i + 1;  // 给 arr1 赋值 1,2,...n
        cout << "arr1[" << i << "] = " << arr1[i] << ", ";
        cout << "arr2[" << i << "] = " << arr2[i] << endl;
    }
    
    // 关键：释放数组必须用 delete[]（不能用 delete！）
    delete[] arr1;  // 释放数组，[] 告诉编译器：释放的是连续的数组内存
    delete[] arr2;
    arr1 = nullptr;
    arr2 = nullptr;
    
    return 0;
}

```

new分配delete释放,new[]分配delete[]释放

4.动态分配类对象

首先了解什么是类什么是对象：

类是模板，只负责定义产品的标准，定义“有什么属性的对象、对象能做什么行为“，而对象则是根据类这个模板这个规则创造出来的产品，且类本身不占用实际空间，一个类能创建无数个对象

(1)Person类：

```c
class Person {
public:  // 公有成员（外部可访问：构造函数、showInfo方法）
    // 1. 构造函数：对象创建时自动调用，用于初始化属性
    Person(string name, int age) {
        this->name = name;  // this 指向当前创建的对象，区分参数和成员变量
        this->age = age;
        cout << "Person 构造函数调用：" << name << endl;
    }
    
    // 2. 析构函数：对象释放时自动调用，用于清理资源（如堆内存、文件句柄）
    ~Person() {
        cout << "Person 析构函数调用：" << name << endl;
    }
    
    // 3. 成员方法：对象的行为
    void showInfo() {
        cout << "姓名：" << name << ", 年龄：" << age << endl;
    }

private:  // 私有成员（外部不可直接访问：属性name、age，体现封装）
    string name;  // 对象的属性（数据）
    int age;
};

```

这个类规定了属性(数据）和行为（方法）还有创建/销毁规则（构造函数、构析函数）：每个对象必须有name和age，每个对象能执行`showInfo()`

- **构造函数**：

  - 与类名同名，无返回值（连 `void` 都不能写）；
  - 用于初始化对象，创建对象时**必须调用**（若未自定义，编译器会生成默认无参构造函数）；
  - 可重载（如定义 `Person()`、`Person(string name)` 等多个构造函数）。

  **析构函数**：

  - 类名前加 `~`，无参数、无返回值；
  - 仅能有一个析构函数（不能重载）；
  - 堆上的对象（`new` 创建）必须用 `delete` 释放，才会调用析构函数；栈上的对象会自动调用析构函数。

  **封装性**：

  - `public`：外部可访问（如构造函数、`showInfo()`）；
  - `private`：外部不可访问（如 `name`、`age`），仅类内部可访问；
  - 目的是隐藏对象的内部状态，避免外部随意修改，仅通过公有接口交互。

(2)创建对象：new动态创建（堆内存）

```c
Person* p = new Person("张三", 20);  // 用 Person 类创建对象“张三”
```

`p->showInfo`访问方法，`p->name`访问属性

p本身存在栈上，指向堆上的对象

静态创建（栈内存）

```c
Person p2("李四", 22);  // 栈上创建对象，自动调用构造函数
p.showInfo();           // 栈上对象用 . 访问成员
// 函数结束时，编译器自动调用析构函数释放对象（无需手动 delete）

```

对象能实现类的功能`p->showInfo`p是指针`p2.showInfo`p2是对象

| 访问方式 | 适用场景                            | 示例代码                     |
| -------- | ----------------------------------- | ---------------------------- |
| `->`     | 指针指向对象（p指向堆内存中的对象） | `p->showInfo();`（p 是指针） |
| `.`      | 直接操作对象（`p2`存储在栈内存）    | `p.showInfo();`（p 是对象）  |

new分配类对象的时候会自动调用类的构造函数，delete会自动调用析构函数

```c
#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    // 构造函数（创建对象时自动调用）
    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "Person 构造函数调用：" << name << endl;
    }
    
    // 析构函数（释放对象时自动调用）
    ~Person() {
        cout << "Person 析构函数调用：" << name << endl;
    }
    
    void showInfo() {
        cout << "姓名：" << name << ", 年龄：" << age << endl;
    }

private:
    string name;
    int age;
};

int main() {
    // 动态分配 Person 对象：new 会自动调用构造函数（传参）
    Person* p = new Person("张三", 20);  // 输出：Person 构造函数调用：张三
    
    // 访问对象成员（用 -> 运算符，指针访问对象成员）
    p->showInfo();  // 输出：姓名：张三, 年龄：20
    
    // 释放对象：delete 会自动调用析构函数
    delete p;  // 输出：Person 析构函数调用：张三
    p = nullptr;
    
    return 0;
}

```



5.定位new允许在已分配的内存地址上创建对象，不重新分配内存

**new(内存地址)类型(初始值)**

```c
#include <iostream>
using namespace std;

int main() {
    // 1. 先分配一块原始内存（比如栈内存或堆内存）
    char buf[sizeof(int)];  // 栈内存，大小等于 int
    
    // 2. 定位 new：在 buf 指向的内存上创建 int 对象（赋值为 10）
    int* p = new (buf) int(10);
    
    cout << "值：" << *p << endl;  // 输出 10
    cout << "地址：" << (void*)p << ", buf地址：" << (void*)buf << endl;  // 地址相同（同一内存）
    
    // 注意：定位 new 分配的内存，若在栈上，无需 delete（栈内存自动释放）；
    // 若在堆上，需手动调用析构函数（如果是类对象），再释放内存。
    
    return 0;
}

```

指针声明是初始化:`int*p=nullptr`		

new分配内存失败：抛出`std::bad_alloc`异常，定义在`<new>`头文件