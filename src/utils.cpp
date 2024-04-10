//
// Created by Don Yihtseu on 11/04/2024.
//
#include <utils.hpp>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md4.h>
#include <cryptopp/md5.h>
#include <cryptopp/sha.h>

using CryptoPP::byte;
using CryptoPP::Weak1::MD4;
using CryptoPP::Weak1::MD5;
using CryptoPP::SHA1;

namespace dogcom {

std::string md4(std::string_view data) {
    std::string digest;
    MD4 hash;
    hash.Update(reinterpret_cast<const byte*>(&data[0]) , data.size());
    digest.resize(hash.DigestSize());
    hash.Final(reinterpret_cast<byte*>(&digest[0]));
    return std::move(digest);
}

std::string md5(std::string_view data) {
    std::string digest;
    MD5 hash;
    hash.Update(reinterpret_cast<const byte*>(&data[0]) , data.size());
    digest.resize(hash.DigestSize());
    hash.Final(reinterpret_cast<byte*>(&digest[0]));
    return std::move(digest);
}

std::string sha(std::string_view data) {
    std::string digest;
    SHA1 hash;
    hash.Update(reinterpret_cast<const byte*>(&data[0]) , data.size());
    digest.resize(hash.DigestSize());
    hash.Final(reinterpret_cast<byte*>(&digest[0]));
    return std::move(digest);
}


}