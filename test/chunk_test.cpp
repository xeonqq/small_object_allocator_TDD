//
// Created by qq on 02.03.19.
//


#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <vector>

#include "include/chunk.h"
#include "test/param_test_fixture.h"

TEST(ChunkTest, WhenAllocateOnNewlyConstructedChunk_ExpectAllocateSuccessful) {
    Chunk chunk{8, 128};
    auto p =chunk.allocate(8);
    EXPECT_NE(p, nullptr);
}

TEST(ChunkTest, WhenAllocateOnFullyOccupiedChunk_ExpectAllocationReturnNullptr) {

    unsigned char num_of_blocks = 128;
    Chunk chunk{8, num_of_blocks};
    for (unsigned i{0};i<num_of_blocks;++i)
    {
        auto p = chunk.allocate(8);
        EXPECT_NE(p, nullptr);
    }
    EXPECT_TRUE(chunk.full());
    auto p = chunk.allocate(8);
    EXPECT_EQ(p, nullptr);
}

INSTANTIATE_TEST_CASE_P(
        ParamTest,
        BlockSizeParamTestFixture,
        ::testing::Values(
                4,8,16,32
        ));
TEST_P(BlockSizeParamTestFixture, WhenAllocatingContinuously_ExpectAllocatedMemoryHasInceasingAddressWithSameInterval) {
    auto block_size = GetParam();
    Chunk chunk{block_size, 128};
    auto p = chunk.allocate(block_size);
    for (size_t i{0};i<128-1;++i)
    {
        auto new_p = chunk.allocate(block_size);
        size_t mem_diff = static_cast<u_char*>(new_p)-static_cast<u_char *>(p);
        p = new_p;
        EXPECT_EQ(mem_diff, block_size);
    }
}

TEST(ChunkTest, WhenAllocateAndDeallocateOnNewlyConstructedChunk_ExpectAllocateAndDeallocationSuccessful) {
    Chunk chunk{8, 16};
    auto p = chunk.allocate(8);
    EXPECT_EQ(*static_cast<unsigned char*>(p), 1);
    *static_cast<int*>(p) = 42;
    EXPECT_NE(p, nullptr);
    chunk.deallocate(p, 8);
    EXPECT_EQ(*static_cast<unsigned char*>(p), 1);
    EXPECT_TRUE(chunk.empty(16));
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

    unsigned char num_of_blocks = 128;
    Chunk chunk{8, num_of_blocks};
    std::vector<void* > ptrs;
    for (unsigned i{0};i<num_of_blocks/2;++i)
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
    for (unsigned i{0};i<num_of_blocks;++i)
    {
        auto p = chunk.allocate(8);
        EXPECT_NE(p, nullptr);
    }
    auto p = chunk.allocate(8);
    EXPECT_EQ(p, nullptr);
}