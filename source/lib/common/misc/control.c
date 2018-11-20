#include "headers/control.h"
#include "headers/constants.h"
#include "../misc/headers/messages.h"

int ask_for_operation(char * op){
    
    fgets(op, DEFAULT_FRAGMENT_MAX_SIZE, stdin);
    int n = strlen(op);
    op[n-1] = '\0';

    if (strcmp(op, "$disconnect") == 0){
        op[0] = '\0';
        return DISCONNECT;
    }
    else if (strcmp(op, "$quit") == 0){
        op[0] = '\0';
        return QUIT;
    }
    else if (strcmp(op, "$client") == 0){
        op[0] = '\0';
        return CLIENT_INFO;
    }
    else if (strcmp(op, "$stats") == 0){
        op[0] = '\0';
        return STATISTICS;
    }
    else if (strcmp(op, "$chat") == 0){
        op[0] = '\0';
        return CHAT;
    }
    else if (strcmp(op, "$sendfile") == 0){
        op[0] = '\0';
        return SEND_FILE;
    }
    else if (strcmp(op, "$server") == 0){
        op[0] = '\0';
        return SERVER_INFO;
    }
    else{
        return CHAT;
    }

    // print_message(FAIL, "No such operation");

    return NO_VAL;
}