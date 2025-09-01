#include "zasuo-net/addresses.h"
#include "zasuo-net/net-logs.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

static const int dns_ips_v4_size;
static const int dns_ips_v6_size;
static const char *dns_ips_v4[];
static const char *dns_ips_v6[];

static int get_local_ip_by_dns(int type, const char *dns_ip, char *ip);


const char *get_local_ip(int type){
    if(type == TYPE_IPV4){
        char *ip = malloc(INET_ADDRSTRLEN);

        for(int i = 0; i < dns_ips_v4_size; i++){
            if(get_local_ip_by_dns(type, dns_ips_v4[i], ip) == 0){
                return ip;
            }
        }
    }else if(type == TYPE_IPV6){
        char *ip = malloc(INET6_ADDRSTRLEN);

        for(int i = 0; i < dns_ips_v6_size; i++){
            if(get_local_ip_by_dns(type, dns_ips_v6[i], ip) == 0){
                return ip;
            }
        }
    }

    return NULL;
}


static int get_local_ip_by_dns(int type, const char *dns_ip, char *ip){
    LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: start");

    if(type == TYPE_IPV4){
        LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: ipv4");
        
        // create upd socket
        int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock_fd < 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: socket failed");
            return -1;
        }

        // create sock addr from dns ip string
        struct sockaddr_in dns_addr4, addr4;
        dns_addr4.sin_family = AF_INET;
        dns_addr4.sin_port = htons(53);
        if(inet_pton(AF_INET, dns_ip,  &dns_addr4.sin_addr) <= 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: dns socket addr failed");
            return -1;
        }

        // connect to the dns server
        if(connect(sock_fd, (struct sockaddr *)&dns_addr4, sizeof(dns_addr4)) < 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: connection failed");
            return -1;
        }

        //get the socket addr
        socklen_t addr4_size = sizeof(addr4);
        if(getsockname(sock_fd, (struct sockaddr *)&addr4, &addr4_size) < 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: get socket name failed");
            return -1;
        }

        // the socket is not needed anymore
        close(sock_fd);

        // get the ip string from sock addr
        if(inet_ntop(AF_INET, &addr4.sin_addr, ip, INET_ADDRSTRLEN) == NULL){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: failed to get ip string");
            return -1;
        }       
    }else{
        LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: ipv6");
        
        // create upd socket
        int sock_fd = socket(AF_INET6, SOCK_DGRAM, 0);
        if(sock_fd < 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: socket failed");
            return -1;
        }

        // create sock addr from dns ip string
        struct sockaddr_in6 dns_addr6, addr6;
        dns_addr6.sin6_family = AF_INET6;
        dns_addr6.sin6_port = htons(53);
        if(inet_pton(AF_INET6, dns_ip,  &dns_addr6.sin6_addr) <= 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: dns socket addr failed");
            return -1;
        }

        // connect to the dns server
        if(connect(sock_fd, (struct sockaddr *)&dns_addr6, sizeof(dns_addr6)) < 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: connection failed");
            return -1;
        }

        //get the socket addr
        socklen_t addr6_size = sizeof(addr6);
        if(getsockname(sock_fd, (struct sockaddr *)&addr6, &addr6_size) < 0){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: get socket name failed");
            return -1;
        }

        // the socket is not needed anymore
        close(sock_fd);

        // get the ip string from sock addr
        if(inet_ntop(AF_INET6, &addr6.sin6_addr, ip, INET6_ADDRSTRLEN) == NULL){
            LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: failed to get ip string");
            return -1;
        }       
    }

    LOG_MSG(LOG_DEBUG, "get_local_ip_by_dns: finished");
    return 0;
}



static int get_local_ip_by_interfaces(){

}

static const char *dns_ips_v4[] = {
    "8.8.8.8",  
    "1.1.1.1",  
    "9.9.9.9",  
    "208.67.222.222"
};

static const int dns_ips_v4_size = 4;

static const char *dns_ips_v6[] = {
    "2001:4860:4860::8888",
    "2606:4700:4700::1111",
    "2620:fe::fe",
    "2620:119:35::35"
};

static const int dns_ips_v6_size = 4;