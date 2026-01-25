lambda

**匿名函数**（也叫 lambda 表达式），核心作用是「就地定义短小的函数逻辑」，无需单独声明函数 / 仿函数，尤其适合作为算法（如 `std::sort`/`std::for_each`）的回调参数

```c++
[capture](parameters) mutable noexcept -> return_type {
    function_body;
}

```

| 组成部分          | 说明                                                   | 可选 / 必选 |
| ----------------- | ------------------------------------------------------ | ----------- |
| `[capture]`       | 捕获列表：决定 lambda 能否访问外部作用域的变量（核心） | 必选        |
| `(parameters)`    | 参数列表：和普通函数的参数一致，可省略（无参数时）     | 可选        |
| `mutable`         | 可变修饰：允许 lambda 修改按值捕获的变量（默认只读）   | 可选        |
| `noexcept`        | 异常说明：声明 lambda 不抛出异常                       | 可选        |
| `-> return_type`  | 返回值类型：可省略（编译器自动推导）                   | 可选        |
| `{function_body}` | 函数体：具体逻辑                                       | 必选        |