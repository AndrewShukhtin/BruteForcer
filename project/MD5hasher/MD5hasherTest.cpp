#include "MD5hasher.hpp"

#include <gtest/gtest.h>

#include <unordered_map>

TEST(MD5hasher, isValidHash) {
    std::unordered_map<std::string, std::string> map = {
        {"00000000", "dd4b21e9ef71e1291183a46b913ae6f2"},
        {"12345678", "25d55ad283aa400af464c76d713c07ad"},
        {"85762034", "8a6f767ad1c8ecd2584194aca2b60cc2"},
        {"99999999", "ef775988943825d2871e1cfa75473ec0"}
    };

    MD5Hasher hasher;
    for (const auto & [currentValue, currentHash] : map) {
        const auto computedHash = hasher(currentValue);
        EXPECT_EQ(currentHash, computedHash);
    }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}