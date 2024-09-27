# 参考: https://github.com/baidu/sofa-pbrpc/blob/master/bazel/snappy.BUILD

package(default_visibility = ["//visibility:public"])

genrule(
    name = "snappy_stubs_public_h",
    srcs = [
        "snappy-stubs-public.h.in",
    ],
    outs = [
        "snappy-stubs-public.h",
    ],
    cmd = "sed 's/$${HAVE_SYS_UIO_H_01}/1/g' $(<) | " +
          "sed 's/$${PROJECT_VERSION_MAJOR}/1/g' | " +
          "sed 's/$${PROJECT_VERSION_MINOR}/1/g' | " +
          "sed 's/$${PROJECT_VERSION_PATCH}/8/g' >$(@)",
    visibility = ["//visibility:private"],
)

cc_library(
    name = "snappy",
    srcs = [
        "snappy.cc",
        "snappy-c.cc",
        "snappy-sinksource.cc",
        "snappy-stubs-internal.cc",
    ],
    hdrs = [
        "snappy.h",
        "snappy-c.h",
        "snappy-internal.h",
        "snappy-sinksource.h",
        "snappy-stubs-internal.h",
        "snappy-stubs-public.h.in",
        ":snappy_stubs_public_h",
    ],
    copts = [
        "-Wno-non-virtual-dtor",
        "-Wno-unused-variable",
        "-Wno-implicit-fallthrough",
        "-Wno-unused-function",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
)
