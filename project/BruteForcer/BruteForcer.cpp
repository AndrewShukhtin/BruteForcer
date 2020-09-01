#include "BruteForcerConfig.hpp"
#include "BruteForcer.hpp"
#include "MD5hasher.hpp"

#include <atomic>
#include <cmath>
#include <future>
#include <thread>
#include <vector>

#include <iostream>

std::atomic<bool> isFound{false};

static std::vector<size_t> getShitfPerThread();

std::pair<bool, std::string> BruteForcer::findPassword(const std::string& hashedPasswd,
                                                       ExecutionPolicy executionPolicy) {
    if (executionPolicy == ExecutionPolicy::PARALLEL) {
        return parallel_find_passwd(hashedPasswd);
    }

    return sequential_find_passwd(hashedPasswd);
}

std::pair<bool, std::string> BruteForcer::parallel_find_passwd(const std::string& hashedPasswd) {
    auto handler = [hashedPasswd](const size_t startNumber, const size_t endNumber) -> std::pair<bool, std::string> {
        MD5Hasher hasher;
        for (size_t currentNumber = startNumber; currentNumber < endNumber; ++currentNumber) {
            auto currentPasswd = convert_to_password(currentNumber);
            auto currentPasswdHash = hasher(currentPasswd);
            if (hashedPasswd == currentPasswdHash) {
                isFound = true;
                return {true, currentPasswd};
            }
            if (isFound) {
                break;
            }
        }

        return {false, {}};
    };

    const auto shifts = getShitfPerThread();
    if (shifts.empty()) {
        return sequential_find_passwd(hashedPasswd);
    }

    std::vector<std::future<std::pair<bool, std::string>>> futures;
    for (size_t i = 1; i < shifts.size(); ++i) {
        futures.push_back(std::async(std::launch::async, handler, shifts[i - 1], shifts[i]));
    }

    for (auto& future : futures) {
        auto [state, foundPasswd] = future.get();
        if (state) {
            return {state, foundPasswd};
        }
    }

    return {false, {}};
}

std::pair<bool, std::string> BruteForcer::sequential_find_passwd(const std::string& hashedPasswd) {
    MD5Hasher hasher;
    for (size_t currentNumber = 0; currentNumber < VARIANTS_COUNT; ++currentNumber) {
        auto currentPasswd = convert_to_password(currentNumber);
        auto currentPasswdHash = hasher(currentPasswd);
        if (hashedPasswd == currentPasswdHash) {
            return {true, currentPasswd};
        }
    }
    return {false, {}};
}

static std::vector<size_t> getShitfPerThread() {
    const size_t numberOfThreads = std::thread::hardware_concurrency();
    if (numberOfThreads == 0) {
        return {};
    }

    const size_t numberOfsegments = numberOfThreads + 1;
    bool isDividable = VARIANTS_COUNT % numberOfsegments == 0;
    size_t shift = (isDividable ?
                        VARIANTS_COUNT / numberOfsegments :
                        VARIANTS_COUNT / numberOfsegments + 1);

    std::vector<size_t> shifts;
    size_t counter = 0;
    while (counter + shift < VARIANTS_COUNT) {
        shifts.push_back(counter);
        counter += shift;
    }
    shifts.push_back(VARIANTS_COUNT);

    return shifts;
}

std::string BruteForcer::convert_to_password(size_t number) {
    std::string passwd = std::to_string(number);
    std::string zeros(PASSWORD_SIZE - passwd.size(), '0');
    return zeros + passwd;
}
