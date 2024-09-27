licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "zstd",
    srcs = [
        ":libzstd_a",
    ],
    hdrs = glob([
        "lib/**/*.h",
    ]),
    includes = [
        "lib",
    ],
)

genrule(
    name = "libzstd_a",
    srcs = [
        "lib/Makefile",
        "lib/libzstd.mk",
        "lib/libzstd.pc.in",
    ] + glob([
        "lib/*.h",
        "lib/common/*.h",
        "lib/common/*.c",
        "lib/compress/*.h",
        "lib/compress/*.c",
        "lib/decompress/*.h",
        "lib/decompress/*.c",
        "lib/decompress/*.S",
        "lib/deprecated/*.h",
        "lib/deprecated/*.c",
        "lib/dictBuilder/*.h",
        "lib/dictBuilder/*.c",
        "lib/legacy/*.h",
        "lib/legacy/*.c",
    ]),
    outs = [
        "libzstd.a",
    ],
    cmd = "make -C `dirname $(location lib/Makefile)` && " +
          "cp `dirname $(location lib/Makefile)`/libzstd.a $@",
)
