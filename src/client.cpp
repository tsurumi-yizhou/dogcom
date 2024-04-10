//
// Created by Don Yihtseu on 11/04/2024.
//
#include <client.hpp>

namespace dogcom {

client_t::client_t(const config_t &info): config(info), socket(service) {

}

}