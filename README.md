# bazel_deps

**[English](README.md)** | **[中文](README_CN.md)**

Bazel BUILD rules for popular C/C++ open-source libraries that don't natively support Bazel.

Each library ships with a `.bzl` workspace rule, a custom `.BUILD` file, and a smoke test under `test/` to verify correctness.

## Supported Libraries

| Library | Version | Type |
|---------|---------|------|
| [LevelDB](https://github.com/google/leveldb) | v1.20 | Key-value store |
| [spdlog](https://github.com/gabime/spdlog) | v1.13.0 | Logging (header-only) |
| [LZ4](https://github.com/lz4/lz4) | v1.9.4 | Compression |
| [GoogleTest](https://github.com/google/googletest) | v1.14.0 | Testing framework |

## Quick Start

### 1. Add bazel_deps to your project

In your `WORKSPACE` file:

```python
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "bazel_deps",
    branch = "main",
    remote = "https://github.com/dddw1216/bazel_deps.git",
)
```

### 2. Load the libraries you need

```python
# Pick what you need
load("@bazel_deps//bazel_deps/spdlog:spdlog.bzl", "spdlog_workspace")
spdlog_workspace()

load("@bazel_deps//bazel_deps/leveldb:leveldb.bzl", "leveldb_workspace")
leveldb_workspace()

load("@bazel_deps//bazel_deps/lz4:lz4.bzl", "lz4_workspace")
lz4_workspace()

load("@bazel_deps//bazel_deps/googletest:googletest.bzl", "googletest_workspace")
googletest_workspace()
```

### 3. Use in BUILD files

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

## Development

### Prerequisites

A Docker container named `dev` (standard Ubuntu with Bazel) is used for building and testing. The host `~/project` directory is mounted inside the container.

```bash
# Enter the dev container
docker exec -it -w /Users/mengdandan/project/bazel_deps dev bash

# Build all active targets
bazel build ...

# Build with debug symbols
bash build.sh debug

# Run a specific test
bazel run //test/lz4:lz4_test

# Format BUILD files
bash buildifier.sh

# Clean everything
bash clean.sh
```

### Project Structure

```
bazel_deps/
├── WORKSPACE                    # Dependency registry
├── .bazelrc                     # Build config (C++17, platform settings)
├── bazel_deps/
│   └── <library>/
│       ├── <library>.bzl        # Download & workspace rule
│       ├── <library>.BUILD      # Bazel build rules
│       └── BUILD                # Package marker
└── test/
    └── <library>/
        ├── BUILD                # Test target
        └── <test>.cc            # Smoke test source
```

### Adding a New Library

1. Create `bazel_deps/<name>/` with a `.bzl` file (download config) and a `.BUILD` file (compile rules)
2. Add an empty `BUILD` file in the same directory
3. Load and call the workspace rule in `WORKSPACE`
4. Write a smoke test under `test/<name>/`
5. Build and verify in the Docker container

## License

Apache License 2.0
