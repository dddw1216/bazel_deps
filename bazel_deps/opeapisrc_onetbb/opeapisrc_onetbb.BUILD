licenses(['notice'])

package(default_visibility = ['//visibility:public'])

cc_library(
  name = "tbb",
  hdrs = glob([
    "include/oneapi/tbb/*.h",
    "include/oneapi/tbb/internal/*.h",
  ]),
  srcs = glob([
    "src/tbb/*.cpp",
    "src/tbb/*.h",
    "include/oneapi/tbb/*.h",
    "include/oneapi/tbb/detail/*.h",
    "include/oneapi/tbb/internal/*.h",
  ]),
  includes = ["include"],
)