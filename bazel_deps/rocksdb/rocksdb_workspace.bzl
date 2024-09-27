load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def clean_dep(dep):
    return str(Label(dep))

def rocksdb_workspace():
    if not native.existing_rule("com_github_facebook_rocksdb"):
        new_git_repository(
            name = "com_github_facebook_rocksdb",
            remote = "https://github.com/facebook/rocksdb.git",
            tag = "v7.10.2",
            build_file = clean_dep("//bazel_deps/rocksdb:rocksdb.BUILD"),
        )
    if not native.existing_rule("com_github_facebook_zstd"):
        new_git_repository(
            name = "com_github_facebook_zstd",
            remote = "https://github.com/facebook/zstd.git",
            tag = "v1.5.4",
            build_file = clean_dep("//bazel_deps/zstd:zstd.BUILD"),
        )
    if not native.existing_rule("com_github_gflags_gflags"):
        git_repository(
            name = "com_github_gflags_gflags",
            remote = "https://github.com/gflags/gflags.git",
            tag = "v2.2.2",
        )
    if not native.existing_rule("com_github_google_glog"):
        http_archive(
            name = "com_github_google_glog",
            strip_prefix = "glog-0.6.0",
            urls = [
                "https://github.com/google/glog/archive/refs/tags/v0.6.0.zip",
            ],
        )
    if not native.existing_rule("com_github_google_snappy"):
        new_git_repository(
            name = "com_github_google_snappy",
            remote = "https://github.com/google/snappy.git",
            tag = "1.1.10",
            build_file = clean_dep("//bazel_deps/snappy:snappy.BUILD"),
        )
    if not native.existing_rule("com_github_lz4_lz4"):
        new_git_repository(
            name = "com_github_lz4_lz4",
            remote = "https://github.com/lz4/lz4.git",
            tag = "v1.9.4",
            build_file = clean_dep("//bazel_deps/lz4:lz4.BUILD"),
        )
    if not native.existing_rule("com_google_googletest"):
        new_git_repository(
            name = "com_google_googletest",
            remote = "https://github.com/google/googletest",
            tag = "v1.13.0",
            build_file = clean_dep("//bazel_deps/facebook_rocksdb:googletest.BUILD"),
        )
