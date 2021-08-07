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
    *static_cast<int *>(p) = 42;
    EXPECT_NE(p, nullptr);
    fixed_size_allocator.deallocate(p, 8);
    EXPECT_EQ(*static_cast<unsigned char *>(p), 1);
}

TEST(FixedSizeAllocatorTest, GivenOnlyOneChunk_WhenAllocateAfterDeallocate_ExpectDeallocatedMemoryGivenBack) {
    FixedSizeAllocator fixed_size_allocator{8, 16};
    fixed_size_allocator.allocate(8);
    auto p = fixed_size_allocator.allocate(8);
    fixed_size_allocator.allocate(8);
    *static_cast<int *>(p) = 42;
    EXPECT_NE(p, nullptr);
    fixed_size_allocator.deallocate(p, 8);
    auto new_p = fixed_size_allocator.allocate(8);
    EXPECT_EQ(new_p, p);
}

TEST(FixedSizeAllocatorTest, WhenAllocatedMoreThanOneChunk_ExpectAllSuccessfull) {
    unsigned char num_of_blocks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    for (size_t i{0}; i < static_cast<size_t>(num_of_blocks) * 10; ++i) {
        auto p = fixed_size_allocator.allocate(8);
        EXPECT_NE(p, nullptr);
    }
}

TEST(FixedSizeAllocatorTest,
     WhenAllocatedAndDeallocateMoreThanOneChunk_ExpectAllSuccessfull_AndAllMemoryReleasedExceptOne) {
    unsigned char num_of_blocks = 1;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    std::vector<void *> allocated;
    for (size_t i{0}; i < static_cast<size_t>(num_of_blocks) * 2; ++i) {
        auto p = fixed_size_allocator.allocate(8);
        *static_cast<long *>(p) = 42;
        allocated.push_back(p);
        EXPECT_NE(p, nullptr);
    }
    EXPECT_EQ(fixed_size_allocator.number_of_chunks(), 2);

    for (auto p : allocated) {
        fixed_size_allocator.deallocate(p, 8);
    }
    EXPECT_EQ(fixed_size_allocator.number_of_chunks(), 1);
    for (size_t i{0}; i < static_cast<size_t>(num_of_blocks); ++i) {
        fixed_size_allocator.allocate(8);
    }
    fixed_size_allocator.allocate(8);

    EXPECT_EQ(fixed_size_allocator.number_of_chunks(), 2);

}

TEST(FixedSizeAllocatorTest,
     GivenMoreThanOneChunkAndAllChunksFull_WhenAllocateAfterDeallocatingOnFirstChunk_ExpectDeallocatedMemoryGivenBack) {
    unsigned char num_of_blocks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    std::vector<void *> allocated;
    for (size_t i{0}; i < static_cast<size_t>(num_of_blocks) * 2; ++i) {
        auto p = fixed_size_allocator.allocate(8);
        *static_cast<long *>(p) = 42;
        allocated.push_back(p);
        EXPECT_NE(p, nullptr);
    }

    fixed_size_allocator.deallocate(allocated[1], 8);
    auto p = fixed_size_allocator.allocate(8);
    EXPECT_EQ(p, allocated[1]);
}

TEST(FixedSizeAllocatorTest,
     GivenFullChunks_WhenAllocateOneBlockAndDeallocateOneBlockConsequtively_ExpectNewChunkIsCreatedAtFirstTime) {
    unsigned char num_of_blocks = 16;
    FixedSizeAllocator fixed_size_allocator{8, num_of_blocks};
    for (size_t i{0}; i < num_of_blocks; ++i) {
        fixed_size_allocator.allocate(8);
    }
    EXPECT_EQ(fixed_size_allocator.number_of_chunks(), 1);
    auto p = fixed_size_allocator.allocate(8);
    fixed_size_allocator.deallocate(p, 8);
    EXPECT_EQ(fixed_size_allocator.number_of_chunks(), 2);
    for (size_t i{0}; i < 10; ++i) {
        auto new_p = fixed_size_allocator.allocate(8);
        EXPECT_EQ(new_p, p);
        fixed_size_allocator.deallocate(new_p, 8);
        EXPECT_EQ(fixed_size_allocator.number_of_chunks(), 2);
    }
}
