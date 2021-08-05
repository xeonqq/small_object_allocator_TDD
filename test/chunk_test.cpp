//
// Created by qq on 02.03.19.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>
#include <algorithm>
#include <random>

#include "include/chunk.h"

TEST(ChunkTest, WhenAllocateOnNewlyConstructedChunk_ExpectAllocateSuccessful) {
    Chunk chunk{8, 128};
    auto p =chunk.allocate(8);
    EXPECT_NE(p, nullptr);
}

TEST(ChunkTest, WhenAllocateOnFullyOccupiedChunk_ExpectAllocationReturnNullptr) {

    unsigned char num_of_chunks = 128;
    Chunk chunk{8, num_of_chunks};
    for (unsigned i{0};i<num_of_chunks;++i)
    {
        auto p = chunk.allocate(8);
        EXPECT_NE(p, nullptr);
    }
    auto p = chunk.allocate(8);
    EXPECT_EQ(p, nullptr);
}

TEST(ChunkTest, WhenAllocateAndDeallocateOnNewlyConstructedChunk_ExpectAllocateAndDeallocationSuccessful) {
    Chunk chunk{8, 16};
    auto p = chunk.allocate(8);
    EXPECT_EQ(*static_cast<unsigned char*>(p), 1);
    *static_cast<int*>(p) = 42;
    EXPECT_NE(p, nullptr);
    chunk.deallocate(p, 8);
    EXPECT_EQ(*static_cast<unsigned char*>(p), 1);
}

TEST(ChunkTest, WhenAssignValueToAllocatedMemory_ExpectAllValuesValid) {
    Chunk chunk{8, 16};
    std::vector<void*> allocated_ptrs;
    for (size_t i{0};i<16;++i)
    {
        auto p = chunk.allocate(8);
        *static_cast<size_t*>(p) = i;
        allocated_ptrs.push_back(p);
    }
    for (size_t i{0};i<16;++i)
    {
        EXPECT_EQ(*static_cast<size_t*>(allocated_ptrs[i]), i);
    }
}

TEST(ChunkTest, WhenDeallocatingOnFullChunk_ThenAllocateAgain_TheSameAddressDeallocatedShouldBeUsed) {
    Chunk chunk{8, 16};
    std::vector<void*> allocated_ptrs;
    for (size_t i{0};i<16;++i)
    {
        auto p = chunk.allocate(8);
        *static_cast<size_t*>(p) = i;
        allocated_ptrs.push_back(p);
    }
    chunk.deallocate(allocated_ptrs[7], 8 );
    auto p = chunk.allocate(8);

    EXPECT_EQ(p, allocated_ptrs[7]);
}

TEST(ChunkTest, WhenAllocateAndDeallocateRandomly_ExpectDeallocatedMemoryCanBeReused) {

    unsigned char num_of_chunks = 128;
    Chunk chunk{8, num_of_chunks};
    std::vector<void* > ptrs;
    for (unsigned i{0};i<num_of_chunks/2;++i)
    {
        auto p = chunk.allocate(8);
        EXPECT_NE(p, nullptr);
        ptrs.push_back(p);
    }

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(ptrs), std::end(ptrs), rng);

    for (auto p: ptrs)
    {
        chunk.deallocate(p, 8);
    }

    //try to allocate all again
    for (unsigned i{0};i<num_of_chunks;++i)
    {
        auto p = chunk.allocate(8);
        EXPECT_NE(p, nullptr);
    }
    auto p = chunk.allocate(8);
    EXPECT_EQ(p, nullptr);


}