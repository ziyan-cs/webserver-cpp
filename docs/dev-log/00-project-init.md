# Project Initialization

## 目标

建立项目的目录、构建和开发工具配置，为后续实现网络服务器做准备。

## 结果

- 建立 `include/`、`src/`、`tests/` 和 `docs/` 目录。
- 配置 CMake、Ninja 和 Debug、Release、RelWithDebInfo 预设。
- 配置 clang-format、clang-tidy、clangd 和 GitHub Actions。
- Debug 预设已用于构建项目；服务器功能在此阶段尚未实现。

## 关键问题

### 编译工具如何获取项目参数？

**处理**：通过 CMake 生成 `compile_commands.json`，供 clangd 等工具读取编译参数。

**限制**：当前 `.clangd` 指向 `build/debug`，需要先配置 Debug 预设。

## 设计决定

- 使用 C++20 和 Linux，围绕 epoll 学习网络编程。
- 使用 CMake 和 CTest；不同构建类型使用独立目录。
- 使用 `main` 保存稳定版本，`develop` 集成开发成果，功能在独立分支开发。

## 待办

- [ ] 实现并验证事件驱动的基础组件，记录见 [Reactor Core](<./01-reactor-core.md>)。
