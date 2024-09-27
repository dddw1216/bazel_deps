package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "concurrent_hash_map",
  srcs = glob([
    "*.h",
    "*.cc",
  ]),
  deps = [
    "@com_github_opeapisrc_onetbb//:tbb",
  ],
  linkopts = [
    "-pthread",
    "-ldl",
  ],
)