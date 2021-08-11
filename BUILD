load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "small_object_allocator",
    srcs = glob([
        "src/*.cpp",
    ]),
    hdrs = glob(["include/*.h"]),
    deps = ["@loki"],
)

cc_test(
    name = "small_object_allocator_unittest",
    srcs = glob(["test/*"]),
    deps = [
        ":small_object_allocator",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "small_object_allocator_benchmark_test",
    srcs = ["test/benchmark/small_object_allocator_benchmark_test.cpp"],
    deps = [
        ":small_object_allocator",
        "@com_google_googlebenchmark//:benchmark",
        "@com_google_googlebenchmark//:benchmark_main",
        "@com_google_googletest//:gtest",
    ],
)
