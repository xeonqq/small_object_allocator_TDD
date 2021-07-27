load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "small_object_allocator",
    srcs = glob([
        "src/*.cpp",
    ]),
    hdrs = glob(["include/.h"]),
)

cc_test(
    name = "small_object_allocator_unittest",
    srcs = glob(["test/**"]),
    deps = [
        ":small_object_allocator",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)
