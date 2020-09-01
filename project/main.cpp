#include "BruteForcer.hpp"

#include <iostream>

const char TIP[] = "Usage: brutef <MD5 hashed password>";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << TIP << std::endl;
        return EXIT_FAILURE;
    }
    
    BruteForcer bruteForcer;
    auto [state, passwd] = bruteForcer.findPassword(argv[1], ExecutionPolicy::PARALLEL);
    if (!state) {
        return EXIT_FAILURE;
    }

    std::cout << passwd << std::endl;
    return EXIT_SUCCESS;
}
