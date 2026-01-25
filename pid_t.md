pid_t

在 Linux 中通常定义在 `<sys/types.h>` 头文件里（`<unistd.h>` 会间接包含它），它的核心作用是：**统一表示进程 ID、父进程 ID、子进程 ID 等进程标识**，不同系统（Linux/UNIX/macOS）对进程 ID 的存储长度可能不同（32 位 / 64 位），用`pid_t`可以避免直接用`int`/`long`导致的兼容性问题；

是有符号整数：

正数：有效的进程 ID（Linux 中进程 ID 从 1 开始，1 是 init 进程）；

0：表示当前进程所在的进程组 ID；

-1：表示 “所有进程”（如`waitpid(-1, &status, 0)`表示等待任意子进程）；

其他负数：表示进程组 ID（取绝对值）

- 子进程中`child_pid=0`：区分父子进程逻辑；
- 父进程中`child_pid>0`：拿到子进程 PID，用于`waitpid()`等待指定子进程；
- `child_pid=-1`：fork 失败，触发错误处理。