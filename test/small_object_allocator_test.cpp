//
// Created by qq on 02.03.19.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>
struct SmallObject
{
    virtual ~SmallObject()=default;
};

TEST(SmallObjectAllocatorTest, WhenFooThenBar) {

    size_t number_of_small_objects=1000;
    std::vector<std::unique_ptr<SmallObject>> small_objects;
    small_objects.reserve(number_of_small_objects);
    for (size_t i{0};i<number_of_small_objects;++i)
    {
        small_objects.push_back(std::make_unique<SmallObject>());
    }
  //EXPECT_EQ(cv::countNonZero(diff), 0);
}
