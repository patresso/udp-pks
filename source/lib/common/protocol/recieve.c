#include "headers/recieve.h"
#include "headers/definitions.h"
#include "../misc/headers/constants.h"
#include "headers/message_processing.h"
#include "../misc/headers/messages.h"
#include "../misc/headers/crc.h"

MESSAGE * recieve(THREAD_ARGS * args){

    int n;
    char * buffer = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);
    socklen_t len = sizeof(*args->address);
    n = recvfrom(args->sockfd, buffer, DEFAULT_FRAGMENT_MAX_SIZE, 0, (struct sockaddr *)args->address, &len);
    if (n < 0) print_message(FAIL, "Message not recieved properly");

    MESSAGE * new = parse_from_bytes(buffer);

    // if (check_integrity(new) != OK){
    //     addtolist(new, args->broken);
    // }

    if (check_integrity(new) != OK) new->checksum = 0;

    return new;
}
