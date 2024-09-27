package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "lrucache",
  srcs = glob([
    "*.h",
    "*.cc",
  ]),
  deps = [
    "@com_github_google_leveldb//:leveldb",
  ],
  linkopts = [
    "-pthread",
    "-ldl",
  ],
)