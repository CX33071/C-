`this`指针

**只有非静态成员变量占对象空间**

1.本质：`this`是为非静态成员函数提供的一个常量指针，指向调用该成员函数的当前对象,隐式提供不用声明

简单说**哪个对象调用成员函数，`this`就指向哪个对象**

2.特性：

- 隐含：无需声明，编译器自动在成员函数参数列表中添加，调用时自动传对象地址
- 常量：`this`是`T*const`，指针的指向不可改，指向成员函数，指向的对象内容可改，不能给`this`赋值
- 作用域：仅在非静态成员函数内部可用，静态成员函数/全局函数无`this`指针
- 作为函数参数存在栈中

3.**this->非静态成员变量，不是+对象名**，因为`this`指向的对象已经确定，此时`this`访问的就是这个对象的非静态成员变量

```c++
class Person {
public:
    int mA;
    void func() {
        cout << "mA:" << mA << endl;  // 等价于 this->mA
    }
};

Person p;
p.mA = 10;
p.func();

```

编译器编译后：将对象的地址传给`this`

```c++
// 成员函数被编译器改写为：添加隐藏的this参数
void Person_func(Person* const this) {  // this是const指针，不能指向其他对象
    cout << "mA:" << this->mA << endl;
}

// 函数调用被编译器改写为：传递对象地址给this
Person p;
p.mA = 10;
Person_func(&p);  // 把p的地址传给this参数

```

4.作用

(1)区分成员变量和局部变量(同名时)：用`this->`明确指向成员变量

```c++
class Person {
public:
    int mA;
    // 形参和成员变量同名，必须用this区分
    void setA(int mA) {
        this->mA = mA;  // this->mA 是成员变量，mA 是形参
    }
};

```

(2)成员函数中返回当前对象

返回`*this`，解引用`this`，得到当前对象：

```c++
class Person {
public:
    int mA;
    Person& setA(int a) {  // 返回对象引用（避免拷贝）
        mA = a;
        return *this;  // 返回当前对象本身
    }
    Person& setB(int b) {
        mB = b;
        return *this;
    }
private:
    int mB;
};

// 链式调用：连续设置属性
Person p;
p.setA(10).setB(20);  // 先调用setA，返回p；再用p调用setB

```

(3)显式访问当前对象的成员，增强可读性

```c++
void func(){
cout<<"mA:"<<this->mA<<endl;//显式标注：访问当前对象的mA
}
```

5.误区：

`this`不占对象内存，`this=new Person();`错误，`this`是`const`指针，不能赋值

```c++
class Person {
public:
    void func1() {  // 无this访问，空指针调用不崩溃
        cout << "func1调用" << endl;
    }
    void func2() {  // 有this访问，空指针调用崩溃
        cout << "mA:" << this->mA << endl;
    }
};

Person* p = nullptr;
p->func1();  // 正常输出：func1调用（无this访问）
p->func2();  // 崩溃：访问空指针的mA

```

空指针调用成员函数不一定崩溃

`const`修饰成员函数

**`void person()const{}`**称为常函数，常函数成员属性不可改，只有成员属性前加`mutable`才能被修改

```c++
class Person{
public:
Person(){
m_a=10;
m_b=10;
}
void showperson const(){
m_a=20;
m_b=20;
}
public:
int m_a;
mutable int m_b;
}
```

`const`修饰对象

`const Person ma;`常对象，只能调用常函数，能改变`mutable`成员变量，不能改变普通成员变量

```c++
void test01() {

	const Person person; //常量对象  
	cout << person.m_A << endl;
	//person.mA = 100; //常对象不能修改成员变量的值,但是可以访问
	person.m_B = 100; //但是常对象可以修改mutable修饰成员变量

	//常对象访问成员函数
	person.MyFunc(); //常对象只能调用const的函数

}
```





