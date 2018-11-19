#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/common/misc/headers/intro.h"
#include "lib/common/misc/headers/messages.h"
#include "lib/client/headers/client.h"
#include "lib/server/headers/server.h"

int main(void){

    int side;
    for (side = NO_VAL; side == NO_VAL; side = intro());

    if (side == SERVER_SIDE){
        int port;
        for (port = NO_VAL; port < 1024 || port > 50000; port = ask_for_port());

        print_message(INFO, "Server is starting");
        server(port);
    }
    else if (side == CLIENT_SIDE){
        in_addr_t addr;
        for (addr = NO_VAL; addr == NO_VAL; addr = ask_for_addr());

        int port;
        for (port = NO_VAL; port < 1024 || port > 50000; port = ask_for_port());

        print_message(INFO, "Client is starting");
        client(addr, port);
    }

    return 0;
}