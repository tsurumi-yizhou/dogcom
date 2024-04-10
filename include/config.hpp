//
// Created by Don Yihtseu on 11/04/2024.
//

#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <array>
#include <string>

namespace dogcom {
struct config_t {
    std::string server;
    std::string username;
    std::string password;
    std::array<uint8_t, 4> host_addr;
    std::string host_name;
    std::array<uint8_t, 4> dns_addr;
    std::string mac_addr;
    std::string os_ver;
    std::array<uint8_t, 4> dhcp_server;
    char auth_ver[2];
    int ror_version;
    int keepalive1_mod;
    char pppoe_flag;
    char CONTROLCHECKSTATUS;
    char ADAPTERNUM;
    char IPDOG;
    unsigned char KEEP_ALIVE_VERSION[2];
};
}

#endif //CONFIG_HPP
