//
// Created by root on 8/1/21.
//

#include <gtest/gtest.h>
#include <fstream>

#include "include/fixed_size_allocator.h"

TEST(FixedSizeAllocatorTest, WhenAllocateOnNewlyConstructedChunk_ExpectAllocateSuccessful) {
    FixedSizeAllocator fixed_size_allocator{8, 16};
    auto p = fixed_size_allocator.allocate(8);
    EXPECT_NE(p, nullptr);
}

TEST(FixedSizeAllocatorTest, WhenAllocateAndDeallocateOnNewlyConstructedChunk_ExpectAllocateAndDeallocateSuccessful) {
    FixedSizeAllocator fixed_size_allocator{8, 16};
    auto p = fixed_size_allocator.allocate(8);
    *static_cast<int*>(p) = 42;
    EXPECT_NE(p, nullptr);
    fixed_size_allocator.deallocate(p, 8);
    EXPECT_EQ(*static_cast<unsigned char*>(p), 1);
}

TEST(FixedSizeAllocatorTest, WhenAllocatedMoreThanOneChunk_ExpectAllSuccessfull) {
    unsigned char num_of_blocks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    for (size_t i{0};i<static_cast<size_t>(num_of_blocks)*10;++i)
    {
        auto p = fixed_size_allocator.allocate(8);
        EXPECT_NE(p, nullptr);
    }
}
TEST(FixedSizeAllocatorTest, WhenAllocatedAndDeallocateMoreThanOneChunk_ExpectAllSuccessfull) {
    unsigned char num_of_blocks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    std::vector<void*> allocated;
    for (size_t i{0};i<static_cast<size_t>(num_of_blocks)*10;++i)
    {
        auto p = fixed_size_allocator.allocate(8);
        *static_cast<long*>(p) = 42;
        allocated.push_back(p);
        EXPECT_NE(p, nullptr);
    }

    for (auto p : allocated)
    {
        fixed_size_allocator.deallocate(p, 8);
    }
}

TEST(FixedSizeAllocatorTest, WhenDeallocatingOnFullChunk_ThenAllocateAgain_TheSameAddressDeallocatedShouldBeUsed) {
    unsigned char num_of_blocks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    std::vector<void*> allocated_ptrs;
    for (size_t i{0};i<num_of_blocks*3;++i)
    {
        auto p = fixed_size_allocator.allocate(8);
        *static_cast<size_t*>(p) = i;
        allocated_ptrs.push_back(p);
    }
    fixed_size_allocator.deallocate(allocated_ptrs[7], 8 );
    auto p = fixed_size_allocator.allocate(8);

    EXPECT_EQ(p, allocated_ptrs[7]);
}
