//
// Created by root on 8/8/21.
//

#include <gtest/gtest.h>
#include <fstream>

#include "include/small_object_allocator.h"

TEST(SmallObjectAllocatorTest, WhenAllocateOnConstructedAllocator_ExpectReturnNonNullPtrMemory) {
    SmallObjectAllocator small_object_allocator(8);
    auto p=small_object_allocator.allocate(4);
    EXPECT_NE(p, nullptr);
    EXPECT_EQ(small_object_allocator.num_of_fixed_size_allocators(),1);
}

TEST(SmallObjectAllocatorTest, WhenAllocatingDifferentSize_ExpectReturnNonNullPtrMemory) {
    SmallObjectAllocator small_object_allocator(8);
    auto p1=small_object_allocator.allocate(4);
    auto p2=small_object_allocator.allocate(8);
    EXPECT_NE(p1, nullptr);
    EXPECT_NE(p2, nullptr);
    EXPECT_EQ(small_object_allocator.num_of_fixed_size_allocators(),2);
}

TEST(SmallObjectAllocatorTest, WhenDeallocate_ExpectSuccess) {
    SmallObjectAllocator small_object_allocator(8);
    auto p1=small_object_allocator.allocate(4);
    auto p2=small_object_allocator.allocate(8);
    small_object_allocator.deallocate(p1, 4);
    small_object_allocator.deallocate(p2,8);
    EXPECT_EQ(small_object_allocator.num_of_fixed_size_allocators(),2);
}