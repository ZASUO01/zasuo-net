#include "zasuo-net.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    set_log_level(LOG_DEBUG);
    const char *ip = get_local_ip(TYPE_IPV6);

    if(ip != NULL){
        printf("%s\n", ip);
        free(ip);
    }

    return 0;
}