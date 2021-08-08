//
// Created by root on 8/8/21.
//


#include <gtest/gtest.h>
#include "include/singleton.h"

struct A {
};
TEST(Singleton, WhenGetInstanceTwice_ExpectReturnSameObject) {
    using SingletonA = Singleton<A>;
    A &a1 = SingletonA::get_instance();
    A &a2 = SingletonA::get_instance();
    EXPECT_EQ(&a1, &a2);
}
