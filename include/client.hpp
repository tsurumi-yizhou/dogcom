//
// Created by Don Yihtseu on 11/04/2024.
//

#ifndef DOGCOM_HPP
#define DOGCOM_HPP
#include <string_view>
#include <boost/asio/io_service.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <config.hpp>

using boost::asio::io_service;
using boost::asio::awaitable;
using boost::asio::ip::tcp;

namespace dogcom {

class client_t : std::enable_shared_from_this<client_t> {
    config_t config;
    io_service service;
    tcp::socket socket;
    bool is_jlu_mode;
    std::string seed;

public:
    client_t(const client_t&) = delete;
    explicit client_t(const config_t& info);
    awaitable<void> dhcp_challenge();
    awaitable<void> dhcp_login();
    awaitable<void> pppoe_challenge();
    awaitable<void> pppoe_login();
    awaitable<void> keepalive1();
    awaitable<void> keepalive2();
    awaitable<void> eap_login();
    awaitable<void> eap_fresh();
    awaitable<void> eap_set_ifname();
};

}

#endif //DOGCOM_HPP
