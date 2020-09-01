#include "BruteForcer.hpp"

#include <gtest/gtest.h>

#include <unordered_map>

void testWithExutionPolicy(ExecutionPolicy policy) {
    std::unordered_map<std::string, std::string> map = {
        {"00000003", "82cf9fa647dd1b3fbd9de71bbfb83fb2"}
    };

    for (const auto & [currentValue, currentHash] : map) {
        BruteForcer bruteForcer;
        const auto [_, foundValue] = bruteForcer.findPassword(currentHash, policy);
        EXPECT_EQ(currentValue, foundValue);
    }
}

TEST(BruteForcerTest, isResultCorrectSequential) {
    testWithExutionPolicy(ExecutionPolicy::SEQUENTIAL);
}

TEST(BruteForcerTest, isResultCorrectParallel) {
    testWithExutionPolicy(ExecutionPolicy::PARALLEL);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}