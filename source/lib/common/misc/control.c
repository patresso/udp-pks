#include "headers/control.h"
#include "headers/constants.h"
#include "../misc/headers/messages.h"

int ask_for_operation(){
    char * op = malloc(50*sizeof(char));
    scanf("%s", op);

    if (strcmp(op, "$disconnect") == 0){
        return DISCONNECT;
    }
    else if (strcmp(op, "$quit") == 0){
        return QUIT;
    }
    else if (strcmp(op, "$client") == 0){
        return CLIENT_INFO;
    }
    else if (strcmp(op, "$stats") == 0){
        return STATISTICS;
    }
    else if (strcmp(op, "$chat") == 0){
        return CHAT;
    }
    else if (strcmp(op, "$sendfile") == 0){
        return SEND_FILE;
    }

    print_message(FAIL, "No such operation");

    return NO_VAL;
}