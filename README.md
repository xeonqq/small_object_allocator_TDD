### Re-implementation of small object alloactor from Andrei's book "Modern C++ Design, Generic Programming and Design Patterns Applied", with TDD.

Benchmark result with different number of small objects [16,64,512,1024]:
```
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.19, 0.93, 0.85
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
BM_SmallObjectAllocatorMalloc/16        0.007 ms        0.007 ms        99208
BM_SmallObjectAllocatorMalloc/64        0.026 ms        0.026 ms        26340
BM_SmallObjectAllocatorMalloc/512       0.214 ms        0.214 ms         3251
BM_SmallObjectAllocatorMalloc/1024      0.424 ms        0.423 ms         1677
BM_SmallObjectAllocatorCustom/16        0.012 ms        0.012 ms        60628
BM_SmallObjectAllocatorCustom/64        0.042 ms        0.042 ms        16687
BM_SmallObjectAllocatorCustom/512       0.341 ms        0.341 ms         2093
BM_SmallObjectAllocatorCustom/1024      0.689 ms        0.689 ms         1058
BM_SmallObjectAllocatorLoki/16          0.012 ms        0.012 ms        58600
BM_SmallObjectAllocatorLoki/64          0.047 ms        0.047 ms        13438
BM_SmallObjectAllocatorLoki/512         0.371 ms        0.371 ms         1840
BM_SmallObjectAllocatorLoki/1024        0.764 ms        0.764 ms          934
```
Surprisingly Loki is not the fastest compare to vanlia malloc in C++14, maybe Loki wins in regard to memory efficiency as was mentioned in the book
