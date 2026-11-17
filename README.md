# webserver-cpp

[![CI](https://github.com/ziyan-cs/webserver-cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/ziyan-cs/webserver-cpp/actions/workflows/ci.yml)

A C++20 web server project for learning networking and backend development.

> The project is under active development.

## Current Status

- Basic configuration and console logging.
- An epoll wrapper, event loop, and event channels for fd event dispatch.
- Initial tests for the base components and event loop.

The server entry point is a placeholder; TCP and HTTP support are planned.

## Quick Start

```bash
git clone https://github.com/ziyan-cs/webserver-cpp.git
cd webserver-cpp
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

## Requirements

| Component | Requirement |
| --- | --- |
| Operating System | Linux with `epoll` support |
| Compiler | C++20-compatible compiler |
| CMake | 3.21 or later |
| Build Tool | Ninja (required by CMake presets) |


## Project Structure

```text
webserver-cpp/
├── .github/workflows/  # CI configuration
├── docs/               # Architecture and development notes
├── include/            # Public headers
├── src/                # Implementation
├── tests/              # Tests
├── CMakeLists.txt      # Root build configuration
└── CMakePresets.json   # Configure, build, and test presets
```

## Development

- **CI:** GitHub Actions builds with GCC and Clang and runs tests and code quality checks.
- **Formatting:** `.clang-format` uses Google style with two-space indentation.
- **Static analysis:** `.clang-tidy` configures clang-tidy checks.
- **Branches:** Feature work is integrated into `develop` before merging into `main`.

## Roadmap

- [ ] v0.1: Reactor core and TCP echo server
- [ ] v0.2: TCP connection management and buffering
- [ ] v0.3: HTTP/1.1 parsing and static file responses
- [ ] v0.4: Timers and idle connection cleanup
- [ ] v0.5: Multi-reactor architecture and thread pool
- [ ] v0.6: Asynchronous logging and observability
- [ ] v0.7: Performance testing and optimization


## License

This project is licensed under the [MIT License](LICENSE).
