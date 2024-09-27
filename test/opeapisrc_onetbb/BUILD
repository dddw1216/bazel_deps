package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "concurrent_hash_map",
    srcs = glob([
        "*.h",
        "*.cc",
    ]),
    linkopts = [
        "-pthread",
        "-ldl",
    ],
    deps = [
        "@com_github_opeapisrc_onetbb//:tbb",
    ],
)
