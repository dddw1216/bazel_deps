package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "rocksdb_test",
    srcs = glob([
        "*.h",
        "*.cc",
    ]),
    linkopts = [
        "-pthread",
        "-ldl",
    ],
    deps = [
        "@com_github_facebook_rocksdb//:rocksdb",
    ],
)
