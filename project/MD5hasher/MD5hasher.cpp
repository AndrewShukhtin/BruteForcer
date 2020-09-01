#include "MD5hasher.hpp"

#include <regex>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>

std::string MD5Hasher::operator()(const std::string& passwd) {
        unsigned char result[MD5_DIGEST_LENGTH];
        MD5((unsigned char*)passwd.c_str(), passwd.size(), result);

        std::ostringstream sout;
        sout << std::hex << std::setfill('0');
        for(long long c: result) {
            sout << std::setw(2) << c;
        }
        return sout.str();
}
