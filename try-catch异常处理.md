`try-catch`异常处理

用于捕获程序执行中出现的错误（如系统调用失败、内存分配失败、逻辑错误等），避免程序崩溃，同时提供友好的错误提示

1.语法：

```c++
try {
    // 可能抛出异常的代码块（如调用可能失败的函数、访问越界等）
} catch (异常类型1& e) {
    // 处理类型1的异常（推荐用引用，避免拷贝+支持多态）
} catch (异常类型2& e) {
    // 处理类型2的异常
} catch (...) {
    // 捕获所有未匹配的异常（兜底，可选）
}

```

**`try` 块**：标记 “需要监控异常” 的代码范围，一旦块内代码抛出异常（`throw`），程序立即跳转到匹配的 `catch` 块；

**`catch` 块**：按 “从上到下” 的顺序匹配异常类型，匹配成功则执行块内逻辑，未匹配则继续向上层 `try-catch` 传播（若最终无匹配，程序调用 `std::terminate` 崩溃）；

**`throw`**：主动抛出异常（如 `throw std::runtime_error("文件不存在");`），也可捕获系统 / 库函数抛出的异常（如 `std::system_error`）

```c++
// 原代码片段：封装文件信息到 vector 时捕获异常
std::vector<FileInfo> file_list;
try {
    for (int i = 0; i < count; ++i) {
        if (entries[i]) {
            // FileInfo 构造函数中若 lstat 失败，会抛出 std::system_error
            file_list.emplace_back(dir, entries[i]);
            free(entries[i]);
        }
    }
} catch (const std::exception& e) {
    // 捕获所有标准异常，输出错误信息
    std::cerr << "Error processing file: " << e.what() << "\n";
}

```

2.常见异常类型

`std::system_error`

**作用**：封装系统调用 / 库函数的错误（即 `errno`）

**触发场景**：你的代码中 `lstat`/`scandir`/`readlink` 等系统调用失败时，通过 `throw std::system_error(...)` 抛出；

```c++
catch (const std::system_error& e) {
    // 可获取具体错误码（如 ENOENT=2、EACCES=13）
    std::cerr << "系统错误码：" << e.code().value() << "\n";
    std::cerr << "错误描述：" << e.what() << "\n";
}

```

兜底捕获`std::exception`

**作用**：所有标准异常的基类，捕获所有标准库抛出的异常（相当于 “一网打尽”）；

```c++
catch (const std::exception& e) {
    // 能捕获 std::system_error、std::bad_alloc、std::out_of_range 等所有标准异常
    std::cerr << "Error: " << e.what() << "\n";
}

```

其他常用标准异常（扩展）

| 异常类型                | 典型触发场景                         | 你的代码是否可能遇到？ |
| ----------------------- | ------------------------------------ | ---------------------- |
| `std::bad_alloc`        | `new`/`emplace_back` 内存分配失败    | 是（文件列表过大时）   |
| `std::out_of_range`     | `std::string`/`std::vector` 下标越界 | 是（路径处理时）       |
| `std::invalid_argument` | 传入无效参数（如空路径给 `stat`）    | 是（参数解析时）       |

3.注意事项

- 优先捕获异常引用（`const T&`）

```c++
catch (const std::exception& e) { /* 正确：无拷贝 + 支持多态 */ }
```

加 `const`：保证不修改异常对象，符合 “只读错误信息” 的逻辑；

引用：避免拷贝开销，且能正确获取派生类（如 `std::system_error`）的 `what()` 信息

- 合理使用兜底 `catch (...)`

```c++
try {
    // 可能抛出非标准异常的代码
} catch (const std::exception& e) {
    std::cerr << "Standard error: " << e.what() << "\n";
} catch (...) {
    // 捕获所有未匹配的异常（包括自定义非标准异常）
    std::cerr << "Unknown error occurred\n";
}

```

- 避免在 `catch` 块中吞掉异常

```c++
catch (const std::exception& e) { /* 空块：异常被吞，问题隐藏 */ }
```

正确做法：至少输出错误信息，或重新抛出（`throw;`）让上层处理。