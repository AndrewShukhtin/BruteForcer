#ifndef PROJECT_BRUTEFORCER_BRUTEFORCER_HPP_
#define PROJECT_BRUTEFORCER_BRUTEFORCER_HPP_

#include <string>

enum class ExecutionPolicy {
    SEQUENTIAL,
    PARALLEL
};

class BruteForcer {
public:
    std::pair<bool, std::string> findPassword(const std::string& hashedPasswd, ExecutionPolicy executionPolicy);

private:
    std::pair<bool, std::string> parallel_find_passwd(const std::string& hashedPasswd);
    std::pair<bool, std::string> sequential_find_passwd(const std::string& hashedPasswd);

private:
    static std::string convert_to_password(size_t number);
};

#endif  // PROJECT_BRUTEFORCER_BRUTEFORCER_HPP_