#ifndef PROJECT_MD5HASHER_MD5HASHER_HPP_
#define PROJECT_MD5HASHER_MD5HASHER_HPP_

#include <string>

struct MD5Hasher {
    std::string operator()(const std::string& passwd);
};

bool isValidMD5(const std::string& hashedPasswd);

#endif  // PROJECT_MD5HASHER_MD5HASHER_HPP_