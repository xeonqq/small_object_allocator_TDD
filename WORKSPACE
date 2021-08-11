load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
    urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
)

http_archive(
    name = "com_google_googlebenchmark",
    strip_prefix = "benchmark-1.5.5",
    urls = ["https://github.com/google/benchmark/archive/refs/tags/v1.5.5.zip"],
)

http_archive(
    name = "rules_cc",
    strip_prefix = "rules_cc-40548a2974f1aea06215272d9c2b47a14a24e556",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/40548a2974f1aea06215272d9c2b47a14a24e556.zip"],
)

http_archive(
    name = "loki",
    build_file = "@//:third_party/loki/loki.BUILD",
    sha256 = "9ce81af9ed1a1d8cfaafb2f98685691666f4af4a1243b8afb3b6cc1b1b99435c",
    strip_prefix = "loki-0.1.7",
    urls = ["https://deac-fra.dl.sourceforge.net/project/loki-lib/Loki/Loki%200.1.7/loki-0.1.7.zip"],
)
