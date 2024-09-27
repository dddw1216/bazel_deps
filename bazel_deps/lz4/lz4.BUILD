licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "lz4",
    srcs = [
        "lib/lz4.c",
        "lib/lz4.h",
        "lib/lz4frame.c",
        "lib/lz4frame.h",
        "lib/lz4hc.c",
        "lib/lz4hc.h",
        "lib/xxhash.h",
    ],
    hdrs = [],
    defines = [
        "XXH_PRIVATE_API",
        "LZ4LIB_VISIBILITY=",
    ],
    includes = [
        "lib",
    ],
    linkopts = [],
    textual_hdrs = [
        "lib/xxhash.c",
        "lib/lz4.c",
    ],
)
