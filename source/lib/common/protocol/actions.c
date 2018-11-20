#include "headers/actions.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "headers/headers.h"

int wait_for_connection(THREAD_ARGS * args){

    int n;
    char * buffer = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);
    n = recvfrom(args->sockfd, buffer, DEFAULT_FRAGMENT_MAX_SIZE, 0, (struct sockaddr *)args->clientaddr, (socklen_t*)sizeof(*(args->clientaddr)));

    //process init message
    printf("%s\n", buffer);

    return NO_VAL;

}