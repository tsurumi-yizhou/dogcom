//
// Created by Don Yihtseu on 11/04/2024.
//
#include <client.hpp>

namespace dogcom {

awaitable<void> client_t::eap_login() {
    throw std::runtime_error("Not Implemented");
}

awaitable<void> client_t::eap_fresh() {
    throw std::runtime_error("Not Implemented");
}

awaitable<void> client_t::eap_set_ifname() {
    throw std::runtime_error("Not Implemented");
}


}