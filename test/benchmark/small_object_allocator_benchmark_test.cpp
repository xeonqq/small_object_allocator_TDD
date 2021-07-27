//
// Created by qq on 02.03.19.
//

#include <memory>
#include <vector>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include "include/small_object.h"
#include "include/small_object_malloc.h"

template<typename AllocationPolicy>
struct Algorithm: public AllocationPolicy
{
    virtual void run()=0;
    virtual ~Algorithm()=default;
};

template<typename AllocationPolicy>
struct BFS: Algorithm<AllocationPolicy>{
    virtual void run() override {};
};

template<typename AllocationPolicy>
struct DFS: Algorithm<AllocationPolicy>{
    virtual void run() override {};
};

template<typename AllocationPolicy>
void allocate_deallocate_small_objects(benchmark::State& state){
    size_t number_of_algo_objects=state.range(0);
    std::vector<std::unique_ptr<Algorithm<AllocationPolicy>>> algorithms;
    algorithms.reserve(number_of_algo_objects);
//    std::cout<< "size of DFS obj:" << sizeof(DFS) <<std::endl;
//    auto bfs_ptr = std::make_unique<BFS>();
//    std::cout<< "size of DFS obj ptr" << sizeof(bfs_ptr.get()) <<std::endl;
    for (size_t i{0};i<number_of_algo_objects/2;++i)
    {
        algorithms.push_back(std::make_unique<BFS<AllocationPolicy>>());
    }
    for (size_t i{0};i<number_of_algo_objects/2;++i)
    {
        algorithms.push_back(std::make_unique<DFS<AllocationPolicy>>());
    }

    for (auto& algo: algorithms)
    {
        algo->run();
    }
}

static void BM_SmallObjectAllocatorMalloc(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        allocate_deallocate_small_objects<SmallObjectMalloc>(state);
    }
}
static void BM_SmallObjectAllocatorCustom(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        allocate_deallocate_small_objects<SmallObject>(state);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_SmallObjectAllocatorMalloc)->Unit(benchmark::kMillisecond)->Range(1<<4, 1<<10);
BENCHMARK(BM_SmallObjectAllocatorCustom)->Unit(benchmark::kMillisecond)->Range(1<<4, 1<<10);
// Run the benchmark
//BENCHMARK_MAIN();
