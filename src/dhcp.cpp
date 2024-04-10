//
// Created by Don Yihtseu on 11/04/2024.
//
#include <random>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/log/trivial.hpp>
#include <client.hpp>
#include <utils.hpp>

using boost::asio::buffer;
using boost::asio::async_read;
using boost::asio::async_write;
using boost::asio::use_awaitable;

namespace dogcom {

awaitable<void> client_t::dhcp_challenge() {
    size_t size = 0;
    std::string chanllenge_packet{'\0', 20};
    chanllenge_packet[0] = 0x01;
    chanllenge_packet[1] = 0x02;
    chanllenge_packet[2] = 114 & 0xff;
    chanllenge_packet[3] = 514 & 0xff;
    chanllenge_packet[4] = config.auth_ver[0];

    size = co_await async_write(socket, buffer(chanllenge_packet), use_awaitable);
    BOOST_LOG_TRIVIAL(info) << std::format("Chanllenge send {} bytes", size);

    std::string buff;
    size = co_await async_read(socket, buffer(buff), use_awaitable);
    BOOST_LOG_TRIVIAL(info) << std::format("Chanllenge recv {} bytes", size);

    if (buff[0] != 0x02) {
        BOOST_LOG_TRIVIAL(error) << std::format("Bad chanllenge: {}", buff[0]);
    } else {
        std::copy_n(buff.data() + 4, 4, seed.begin());
    }

    co_return;
}

awaitable<void> client_t::dhcp_login() {
    size_t size = 0;
    std::string login_packet{};

    login_packet[0] = 0x03;
    login_packet[1] = 0x01;
    login_packet[2] = 0x00;
    login_packet[3] = config.username.size() + 20;

    std::ranges::copy(config.username.begin(), config.username.end(), login_packet.begin() + 20);
    login_packet[56] = config.CONTROLCHECKSTATUS;
    login_packet[57] = config.ADAPTERNUM;

    login_packet[80] = 0x01;
    std::ranges::copy(config.host_addr.begin(), config.host_addr.end(), login_packet.begin() + 81);
    login_packet[105] = config.IPDOG;
    std::ranges::copy(config.host_name.begin(), config.host_name.end(), login_packet.begin() + 110);
    std::ranges::copy(config.dns_addr.begin(), config.dns_addr.end(), login_packet.begin() + 142);
    std::ranges::copy(config.dhcp_server.begin(), config.dhcp_server.end(), login_packet.begin() + 146);

    std::array<uint8_t, 4> os_info_size {0x94};
    std::array<uint8_t, 4> os_major {0x05};
    std::array<uint8_t, 4> os_minor{0x01};
    std::array<uint8_t, 4> os_build{0x28, 0x0a};
    std::array<uint8_t, 4> platform{0x02};
    if (is_jlu_mode) {
        os_major[0] = 0x06;
        os_minor[0] = 0x02;
        os_build[0] = 0xf0;
        os_build[1] = 0x23;
        platform[0] = 0x02;
        std::array<uint8_t, 40> service {0x33, 0x64, 0x63, 0x37, 0x39, 0x66, 0x35, 0x32, 0x31, 0x32, 0x65, 0x38, 0x31, 0x37, 0x30, 0x61, 0x63, 0x66, 0x61, 0x39, 0x65, 0x63, 0x39, 0x35, 0x66, 0x31, 0x64, 0x37, 0x34, 0x39, 0x31, 0x36, 0x35, 0x34, 0x32, 0x62, 0x65, 0x37, 0x62, 0x31};
        std::array<uint8_t, 9> hostname{0x44, 0x72, 0x43, 0x4f, 0x4d, 0x00, 0xcf, 0x07, 0x68};
        std::ranges::copy(hostname.begin(), hostname.end(), login_packet.begin() + 182);
        std::ranges::copy(service.begin(), service.end(), login_packet.begin() + 246);
    }
    std::ranges::copy(os_info_size.begin(), os_info_size.end(), login_packet.begin() + 162);
    std::ranges::copy(os_major.begin(), os_major.end(), login_packet.begin() + 166);
    std::ranges::copy(os_minor.begin(), os_minor.end(), login_packet.begin() + 170);
    std::ranges::copy(os_build.begin(), os_build.end(), login_packet.begin() + 174);
    std::ranges::copy(platform.begin(), platform.end(), login_packet.begin() + 178);
    if (!is_jlu_mode) {
        std::ranges::copy(config.os_ver.begin(), config.os_ver.end(), login_packet.begin() + 182);
    }
    std::ranges::copy_n(config.auth_ver, 2, login_packet.begin() + 310);

    size = co_await async_write(socket, buffer(login_packet), use_awaitable);
    BOOST_LOG_TRIVIAL(info) << std::format("Login sent {} bytes", size);

    std::string buff;
    size = co_await async_read(socket, buffer(buff), use_awaitable);

    if (buff[0] != 0x04) {
        BOOST_LOG_TRIVIAL(error) << std::format("Login failed, recv {} bytes", size);
    } else {
        BOOST_LOG_TRIVIAL(info) << "Login succeed";
    }
    co_return;
}


}