# webserver-cpp

## 当前进度 — v0.1：单线程 Echo 服务器

| 项目 | 说明 |
|------|------|
| 运行平台 | Linux |
| 传输协议 | TCP（IPv4） |
| 并发模型 | 单线程、阻塞 I/O |
| 核心 API | POSIX Socket |
| 构建系统 | CMake |

**已实现功能：**
- TCP socket 流程：创建、绑定、监听、接受连接
- 双向通信：接收客户端消息并原样回显
- 优雅退出：支持 `Ctrl+C` 信号处理
- 跨网络验证：宿主机 ↔ 虚拟机 通信正常，支持 Telnet 接入

## 代码结构
- `Logger.h`: 日志宏，提供 `INFO/DEBUG/WARN/ERROR` 四级输出
- `Config`: 封装服务器配置（端口、IP、backlog 等）
- `Socket`: 封装 socket 生命周期与 RAII 资源管理
- `TcpServer`: 核心 echo 逻辑，实现 `accept/recv/send` 流程
- `main.cpp`: 入口文件，支持默认/自定义配置启动

## 项目结构

```text
webserver-cpp/
├── .gitignore
├── CMakeLists.txt
├── README.md
├── docs/
│   └── dev-log/
│       └── v0.1.md
└── src/
    ├── CMakeLists.txt
    ├── log/
    │   ├── CMakeLists.txt
    │   └── Logger.h
    ├── config/
    │   ├── CMakeLists.txt
    │   └── Config.h/.cpp
    ├── net/
    │   ├── CMakeLists.txt
    │   └── Socket.h/.cpp
    └── server/
        ├── CMakeLists.txt
        ├── TcpServer.h/.cpp
        └── main.cpp
```

## 构建与运行

```bash
mkdir build && cd build
cmake ..
make
./webserver
```

用 Telnet 连接测试：

```bash
telnet <server-ip> <port>
```

## 演进路线

- [x] v0.1：TCP echo server —— 纯 socket 实现，跑通完整收发流程
- [ ] v0.2：引入 epoll，改造为事件驱动 I/O 多路复用模型
- [ ] v0.3：HTTP/1.1 请求解析，响应静态页面
- [ ] v0.4：线程池，实现多线程并发处理请求
- [ ] v0.5：小根堆定时器，处理超时连接
- [ ] v0.6：异步日志系统
- [ ] v0.7：MySQL 连接池，用户登录 / 注册
- [ ] v0.8：性能压测、架构图、README 整理、单元测试

## 技术栈

`C++17` · `Linux` · `POSIX Socket` · `CMake`
