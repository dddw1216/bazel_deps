load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def clean_dep(dep):
  return str(Label(dep))

def leveldb_workspace(**kwargs):
  if not native.existing_rule("com_github_google_leveldb"):
    http_archive(
      name = "com_github_google_leveldb",
      url = "https://github.com/google/leveldb/archive/v1.20.zip",
      sha256 = "5b2bd7a91489095ad54bb81ca6544561025b48ec6d19cc955325f96755d88414",
      strip_prefix = "leveldb-1.20",
      build_file = clean_dep("//bazel_deps/leveldb:leveldb.BUILD"),
    )
