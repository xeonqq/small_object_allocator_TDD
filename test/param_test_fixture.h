//
// Created by root on 8/11/21.
//

#ifndef SMALL_OBJECT_ALLOCATOR_PARAM_TEST_FIXTURE_H
#define SMALL_OBJECT_ALLOCATOR_PARAM_TEST_FIXTURE_H
class BlockSizeParamTestFixture : public ::testing::TestWithParam<size_t> {
};

#endif //SMALL_OBJECT_ALLOCATOR_PARAM_TEST_FIXTURE_H
