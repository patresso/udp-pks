#include "headers/recieve.h"
#include "headers/definitions.h"
#include "../misc/headers/constants.h"

MESSAGE * recieve(THREAD_ARGS * args){

    int n;
    char * buffer = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);
    n = recvfrom(args->sockfd, buffer, DEFAULT_FRAGMENT_MAX_SIZE, 0, (struct sockaddr *)args->address, sizeof(args->address));

    MESSAGE * new = parse_from_bytes(buffer);

    return new;
}
