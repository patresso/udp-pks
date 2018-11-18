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
        print_message(INFO, "Server is starting");
        start_server();
    }
    else if (side == CLIENT_SIDE){
        print_message(INFO, "Client is starting");
        start_client();
    }

    return 0;
}