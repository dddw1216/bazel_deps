package(default_visibility = ["//visibility:public"])

cc_library(
    name = "sparsehash_sparsehash",
    hdrs = glob([
        "src/google/**/*",
        "src/sparsehash/**/*",
    ]),
    includes = ["src"],
    deps = [
        "@//bazel_deps/sparsehash_sparsehash:sparsehashconfig",
    ],
)
