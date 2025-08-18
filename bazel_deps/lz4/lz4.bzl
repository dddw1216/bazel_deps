load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def lz4_workspace():
    http_archive(
        name = "lz4",
        urls = ["https://github.com/lz4/lz4/archive/v1.9.4.tar.gz"],
        strip_prefix = "lz4-1.9.4",
        build_file = "//bazel_deps/lz4:lz4.BUILD",
    )
