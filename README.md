# bazel_deps

bazel_deps 是专门针对 github 上开源的 C/C++ 项目，但是不支持 bazel 编译而准备的，编译这些项目的 bazel 文件

每次新增一个新的第三方项目，如 onetbb 或者 spdlog，都需要在 test 创建对应目录，编写一个简单的测试文件，对引入的第三方C++系统库，进行测试，保证引入正确

当引入正确后，就可以发布到 remote main

开发 bazel_deps 需要进入 docker 环境，本地会有一个叫 dev 的 docker 容器（如果没有抛出问题）这个docker 就是一个简单的标准的 ubuntu 环境

进入 dev 之后，项目代码都在路径 /root/project/ 下

## 支持的第三方库

### 1. spdlog - 现代 C++ 日志库
- **版本**: v1.13.0
- **描述**: 高性能的 C++ 日志库，支持多种输出格式和异步日志
- **特性**: 
  - 支持控制台和文件输出
  - 支持按大小和时间滚动
  - 支持多线程
  - 支持格式化日志
  - 仅头文件库，易于集成

### 2. leveldb - Google 键值存储库
- **版本**: v1.20
- **描述**: Google 开发的高性能键值存储库

### 3. onetbb - Intel Threading Building Blocks
- **描述**: Intel 的并行编程库

### 4. googletest - Google 测试框架
- **描述**: Google 的 C++ 测试框架

### 5. 其他库
- jemalloc, lz4, snappy, zstd, rocksdb 等

## 使用方法

### 1. 在项目中引入 bazel_deps

在项目的 WORKSPACE 文件中添加：

```bazel
### bazel_deps
git_repository(
    name = "bazel_deps",
    branch = "main",
    remote = "https://github.com/dddw1216/bazel_deps.git",
)
```

### 2. 使用 spdlog

#### 在 WORKSPACE 中引入

```bazel
load("@bazel_deps//bazel_deps/spdlog:spdlog.bzl", "spdlog_workspace")
spdlog_workspace()
```

#### 在 BUILD 文件中使用

```bazel
cc_library(
    name = "my_library",
    srcs = ["my_library.cc"],
    deps = [
        "@spdlog//:spdlog",
    ],
)
```

#### 在代码中使用

**基本用法**

```cpp
#include <spdlog/spdlog.h>

int main() {
    // 基本日志
    spdlog::info("Hello from spdlog!");
    spdlog::warn("This is a warning message");
    spdlog::error("This is an error message");
    
    // 格式化日志
    spdlog::info("Testing formatted log: {}", 42);
    spdlog::error("Error occurred in function {} at line {}", __FUNCTION__, __LINE__);
    
    return 0;
}
```

**创建自定义 logger**

```cpp
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

int main() {
    // 创建控制台 sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    
    // 创建文件 sink
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/app.log", 10*1024*1024, 3);
    file_sink->set_level(spdlog::level::info);
    
    // 创建 logger
    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    auto logger = std::make_shared<spdlog::logger>("my_logger", sinks.begin(), sinks.end());
    
    // 使用 logger
    logger->info("This message goes to both console and file");
    logger->debug("This message only goes to console");
    
    return 0;
}
```

**异步日志**

```cpp
#include <spdlog/spdlog.h>
#include <spdlog/async.h>

int main() {
    // 创建异步 logger
    auto async_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_logger", "logs/async.log");
    
    // 异步日志不会阻塞主线程
    for (int i = 0; i < 100; ++i) {
        async_logger->info("Async message {}", i);
    }
    
    return 0;
}
```

**日志级别**

spdlog 支持以下日志级别（从低到高）：

- `trace` - 最详细的调试信息
- `debug` - 调试信息
- `info` - 一般信息
- `warn` - 警告信息
- `error` - 错误信息
- `critical` - 严重错误信息

**格式化**

spdlog 使用 fmt 库进行格式化，支持：

```cpp
spdlog::info("String: {}", "hello");
spdlog::info("Number: {}", 42);
spdlog::info("Float: {:.2f}", 3.14159);
spdlog::info("Multiple: {} {} {}", "a", "b", "c");
```

**性能特性**

- **仅头文件库** - 无需编译，直接包含即可使用
- **异步日志** - 支持异步日志，不阻塞主线程
- **高性能** - 经过优化的高性能日志库
- **线程安全** - 完全线程安全

### 3. 使用其他库

类似地，对于其他库：

```bazel
# leveldb
load("@bazel_deps//bazel_deps/leveldb:leveldb.bzl", "leveldb_workspace")
leveldb_workspace()

# onetbb
load("@bazel_deps//bazel_deps/opeapisrc_onetbb:opeapisrc_onetbb.bzl", "opeapisrc_onetbb_workspace")
opeapisrc_onetbb_workspace()
```

## 测试

每个库都有对应的测试文件在 `test/` 目录下，确保库能正常工作：

```bash
# 测试 spdlog
bazel build //test/spdlog_test:spdlog_test
./bazel-bin/test/spdlog_test/spdlog_test
```

## Bazel 模块系统

### MODULE.bazel 和 MODULE.bazel.lock

Bazel 有两种依赖管理方式：

#### 1. WORKSPACE 方式（传统方式）
- 使用 `WORKSPACE` 文件管理外部依赖
- 依赖关系在构建时解析
- 适合复杂的依赖关系和自定义规则

#### 2. MODULE.bazel 方式（新方式）
- 使用 `MODULE.bazel` 文件管理依赖
- 依赖关系在模块解析时确定
- 提供更好的版本管理和依赖解析

**MODULE.bazel 文件示例：**
```bazel
module(
    name = "my_project",
    version = "1.0.0",
)

bazel_dep(name = "rules_cc", version = "0.0.9")
bazel_dep(name = "spdlog", version = "1.13.0")
```

**MODULE.bazel.lock 文件：**
- 自动生成的文件，记录确切的依赖版本
- 确保构建的可重现性
- 类似于 `package-lock.json` 或 `Cargo.lock`

**为什么有些项目使用 MODULE.bazel：**
- 更好的版本管理
- 更快的依赖解析
- 更好的工具支持
- Bazel 官方推荐的新方式

## 项目结构说明

### 为什么有些项目需要 .bzl 文件，有些只需要 .BUILD 文件？

#### 1. 简单项目（只需要 .BUILD 文件）
**适用场景：**
- 仅头文件库（如 spdlog）
- 简单的 C/C++ 库
- 不需要复杂的配置或依赖

**示例：**
```
bazel_deps/spdlog/
├── spdlog.bzl          # 简单的下载配置
├── spdlog.BUILD        # 构建规则
└── BUILD               # 空文件
```

**spdlog.bzl 内容：**
```bazel
def spdlog_workspace(**kwargs):
  if not native.existing_rule("spdlog"):
    http_archive(
      name = "spdlog",
      url = "https://github.com/gabime/spdlog/archive/v1.13.0.tar.gz",
      sha256 = "...",
      strip_prefix = "spdlog-1.13.0",
      build_file = clean_dep("//bazel_deps/spdlog:spdlog.BUILD"),
    )
```

#### 2. 复杂项目（需要 _workspace.bzl 文件）
**适用场景：**
- 有多个子模块或组件
- 需要复杂的配置选项
- 有多个依赖关系
- 需要平台特定的配置

**示例：**
```
bazel_deps/rocksdb/
├── rocksdb.bzl             # 复杂的配置和依赖管理
├── rocksdb.BUILD           # 主构建规则
└── BUILD                   # 空文件
```

**rocksdb.bzl 内容：**
```bazel
def rocksdb_workspace(**kwargs):
  # 可能需要多个依赖
  if not native.existing_rule("com_github_google_snappy"):
    http_archive(...)
  
  if not native.existing_rule("com_github_facebook_zstd"):
    http_archive(...)
  
  # 主库
  if not native.existing_rule("com_github_facebook_rocksdb"):
    http_archive(...)
```

#### 3. 选择标准

**使用简单 .bzl 文件的情况：**
- ✅ 仅头文件库
- ✅ 无外部依赖
- ✅ 简单的构建配置
- ✅ 跨平台兼容性好

**使用复杂 _workspace.bzl 文件的情况：**
- ✅ 有多个子模块
- ✅ 有外部依赖
- ✅ 需要平台特定配置
- ✅ 复杂的构建选项

## 贡献

当需要添加新的第三方库时：

1. 在 `bazel_deps/` 目录下创建新的库目录
2. 创建 `.bzl` 文件定义库的下载和配置
3. 创建 `BUILD` 文件定义编译规则
4. 在 `test/` 目录下创建测试文件
5. 更新 `WORKSPACE` 文件
6. 更新此 README 文件

## 更多信息

- [spdlog 官方文档](https://github.com/gabime/spdlog)
- [fmt 格式化库](https://github.com/fmtlib/fmt)
- [Bazel 模块系统文档](https://bazel.build/external/overview#bzlmod)

## 许可证

本项目采用 Apache License 2.0 许可证。
