#include "headers/send.h"
#include "headers/definitions.h"
#include "../misc/headers/constants.h"
#include "headers/message_processing.h"
#include "../misc/headers/messages.h"

int sendmessage(MESSAGE * msg, THREAD_ARGS * args){
    char * buffer = parse_to_bytes(msg);
    int n = sendto(args->sockfd, buffer, 16+msg->data_length, 0, (const struct sockaddr*)args->address, sizeof(*args->address));
    if (n < 0) print_message(FAIL, "Message not sent");
    
    print_message(INFO, "Sending");
    printf("type: %d\n", msg->message_type);
    return 0;
}