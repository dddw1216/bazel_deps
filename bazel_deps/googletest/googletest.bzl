load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def googletest_workspace():
    http_archive(
        name = "com_google_googletest",
        urls = ["https://github.com/google/googletest/archive/v1.14.0.tar.gz"],
        strip_prefix = "googletest-1.14.0",
        build_file = "//bazel_deps/googletest:googletest.BUILD",
    )
