#include "InetAddress.hpp"

#include "Logger.hpp"

int main(){

    // InetAddress addr(8080,"172.17.168.200");
    // printf("%s - %s - %u\n",addr.toIp().c_str(),addr.toIpPort().c_str(),addr.toPort());

    LOG("message",DEBUG);
    LOG_INFO("info");
    LOG_DEBUG("debug");
    LOG_FATAL("fatal");
    LOG_ERROR("error");



    return 0;
}