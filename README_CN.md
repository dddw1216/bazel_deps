# bazel_deps

**[English](README.md)** | **[中文](README_CN.md)**

为不原生支持 Bazel 构建系统的常用 C/C++ 开源库提供 Bazel BUILD 规则。

每个库包含一个 `.bzl` workspace 规则、一个自定义 `.BUILD` 编译文件，以及 `test/` 下的冒烟测试来验证集成正确性。

## 支持的第三方库

| 库 | 版本 | 类型 |
|----|------|------|
| [LevelDB](https://github.com/google/leveldb) | v1.20 | 键值存储 |
| [spdlog](https://github.com/gabime/spdlog) | v1.13.0 | 日志库（仅头文件） |
| [LZ4](https://github.com/lz4/lz4) | v1.9.4 | 压缩库 |
| [GoogleTest](https://github.com/google/googletest) | v1.14.0 | 测试框架 |

## 快速开始

### 1. 在项目中引入 bazel_deps

在 `WORKSPACE` 中添加：

```python
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "bazel_deps",
    branch = "main",
    remote = "https://github.com/dddw1216/bazel_deps.git",
)
```

### 2. 加载需要的库

```python
# 按需选择
load("@bazel_deps//bazel_deps/spdlog:spdlog.bzl", "spdlog_workspace")
spdlog_workspace()

load("@bazel_deps//bazel_deps/leveldb:leveldb.bzl", "leveldb_workspace")
leveldb_workspace()

load("@bazel_deps//bazel_deps/lz4:lz4.bzl", "lz4_workspace")
lz4_workspace()

load("@bazel_deps//bazel_deps/googletest:googletest.bzl", "googletest_workspace")
googletest_workspace()
```

### 3. 在 BUILD 文件中使用

```python
cc_binary(
    name = "my_app",
    srcs = ["main.cc"],
    deps = [
        "@spdlog//:spdlog",
        "@com_github_google_leveldb//:leveldb",
        "@lz4//:lz4",
    ],
)

cc_test(
    name = "my_test",
    srcs = ["my_test.cc"],
    deps = ["@com_google_googletest//:gtest_main"],
)
```

## 开发指南

### 环境要求

使用名为 `dev` 的 Docker 容器（标准 Ubuntu + Bazel）进行编译和测试。宿主机 `~/project` 目录挂载到容器内。

```bash
# 进入开发容器
docker exec -it -w /Users/mengdandan/project/bazel_deps dev bash

# 编译所有已启用的目标
bazel build ...

# Debug 模式编译
bash build.sh debug

# 运行某个测试
bazel run //test/lz4:lz4_test

# 格式化 BUILD 文件
bash buildifier.sh

# 清理构建产物
bash clean.sh
```

### 项目结构

```
bazel_deps/
├── WORKSPACE                    # 依赖注册表
├── .bazelrc                     # 构建配置（C++17、平台设置）
├── bazel_deps/
│   └── <library>/
│       ├── <library>.bzl        # 下载与 workspace 规则
│       ├── <library>.BUILD      # Bazel 编译规则
│       └── BUILD                # 包标记文件
└── test/
    └── <library>/
        ├── BUILD                # 测试目标
        └── <test>.cc            # 冒烟测试源码
```

### 新增第三方库

1. 创建 `bazel_deps/<name>/` 目录，编写 `.bzl`（下载配置）和 `.BUILD`（编译规则）文件
2. 在同目录下添加空的 `BUILD` 文件
3. 在 `WORKSPACE` 中加载并调用 workspace 规则
4. 在 `test/<name>/` 下编写冒烟测试
5. 进入 Docker 容器编译验证通过后，合入 main 分支

## 许可证

Apache License 2.0
