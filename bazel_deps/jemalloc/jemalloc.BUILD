package(default_visibility = ["//visibility:public"])

cc_library(
    name = "jemalloc",
    srcs = glob(["com_github_jemalloc/src/*.c"]),
    hdrs = glob(["com_github_jemalloc/include/*.h"]),
    copts = [
        "-Iexternal/com_github_jemalloc/include",
    ],
    linkopts = [
        "-ljemalloc",
    ],
)
