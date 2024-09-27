package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "lrucache",
    srcs = glob([
        "*.h",
        "*.cc",
    ]),
    linkopts = [
        "-pthread",
        "-ldl",
    ],
    deps = [
        "@com_github_google_leveldb//:leveldb",
    ],
)
