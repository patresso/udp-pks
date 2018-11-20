#include "headers/send_recieve.h"
#include "headers/headers.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"

HEADER_FULL * recieve_message(THREAD_ARGS * args, int side){

    int n;
    char * buffer = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);
    if (side == SERVER)
        n = recvfrom(args->sockfd, buffer, DEFAULT_FRAGMENT_MAX_SIZE, 0, (struct sockaddr *)args->clientaddr, (socklen_t*)sizeof(*(args->clientaddr)));
    else
        n = recvfrom(args->sockfd, buffer, DEFAULT_FRAGMENT_MAX_SIZE, 0, (struct sockaddr *)args->serveraddr, (socklen_t*)sizeof(*(args->serveraddr)));
    
    return parse_message_from_bytes(buffer);
}

int send_message(THREAD_ARGS * args, HEADER_FULL * msg, int side){

    char * message = convert_to_bytes(msg);
    if (side == SERVER)
        return sendto(args->sockfd, message, DEFAULT_FRAGMENT_MAX_SIZE, 0, (const struct sockaddr *)args->clientaddr, *(socklen_t*)sizeof(*(args->clientaddr)));
    else 
        return sendto(args->sockfd, message, DEFAULT_FRAGMENT_MAX_SIZE, 0, (const struct sockaddr *)args->serveraddr, *(socklen_t*)sizeof(*(args->serveraddr)));
}