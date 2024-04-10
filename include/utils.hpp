//
// Created by Don Yihtseu on 11/04/2024.
//

#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>

namespace dogcom {

std::string md4(std::string_view);
std::string md5(std::string_view);
std::string sha(std::string_view);

}

#endif //UTILS_HPP
