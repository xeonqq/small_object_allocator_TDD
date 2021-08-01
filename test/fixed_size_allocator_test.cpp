//
// Created by root on 8/1/21.
//

#include <gtest/gtest.h>

#include "include/fixed_size_allocator.h"

TEST(FixedSizeAllocatorTest, WhenAllocateOnNewlyConstructedChunk_ExpectAllocateSuccessful) {
    FixedSizeAllocator fixed_size_allocator{8, 16};
    auto p = fixed_size_allocator.allocate(8);
    EXPECT_NE(p, nullptr);
}

TEST(FixedSizeAllocatorTest, WhenAllocatedMoreThanOneChunks_ExpectAllSuccessfull) {
    unsigned char num_of_chunks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_chunks};
    for (size_t i{0};i<static_cast<size_t>(num_of_chunks)*4;++i)
    {
        auto p = fixed_size_allocator.allocate(8);
        EXPECT_NE(p, nullptr);
    }
}