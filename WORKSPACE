load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

load("//bazel_deps/leveldb:leveldb.bzl", "leveldb_workspace")
leveldb_workspace()

load("//bazel_deps/spdlog:spdlog.bzl", "spdlog_workspace")
spdlog_workspace()

load("//bazel_deps/lz4:lz4.bzl", "lz4_workspace")
lz4_workspace()

load("//bazel_deps/googletest:googletest.bzl", "googletest_workspace")
googletest_workspace()
