//
// Created by shepherd on 1.5.24.
//

#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <string>
#include <openssl/sha.h>

namespace c1::utils
{
inline std::string sha256(const std::string& s)
{
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, s.c_str(), s.size());
    SHA256_Final(hash, &sha256);
    std::string hashed_str;
    for (const unsigned char i : hash)
        hashed_str += i;
    return hashed_str;
}
}

// c1::utils

#endif //SECURITY_HPP
