load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def clean_dep(dep):
  return str(Label(dep))

def spdlog_workspace(**kwargs):
  if not native.existing_rule("spdlog"):
    http_archive(
      name = "spdlog",
      url = "https://github.com/gabime/spdlog/archive/v1.13.0.tar.gz",
      sha256 = "534f2ee1a4dcbeb22249856edfb2be76a1cf4f708a20b0ac2ed090ee24cfdbc9",
      strip_prefix = "spdlog-1.13.0",
      build_file = clean_dep("//bazel_deps/spdlog:spdlog.BUILD"),
    )
