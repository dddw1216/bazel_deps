load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def clean_dep(dep):
  return str(Label(dep))

def opeapisrc_onetbb_workspace(**kwargs):
  if not native.existing_rule("com_github_opeapisrc_onetbb"):
    http_archive(
      name = "com_github_opeapisrc_onetbb",
      urls = [
        "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.9.0.tar.gz",
      ],
      sha256 = "1ce48f34dada7837f510735ff1172f6e2c261b09460e3bf773b49791d247d24e",
      strip_prefix = "oneTBB-2021.9.0",
      build_file = clean_dep("//bazel_deps/opeapisrc_onetbb:opeapisrc_onetbb.BUILD"),
    )
