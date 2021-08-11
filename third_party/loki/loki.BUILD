load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "loki",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["include/**/*.h"]),
    strip_include_prefix="include",
    visibility = ["//visibility:public"],
)
