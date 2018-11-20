#include "headers/message_processing.h"
#include "headers/definitions.h"
#include "../misc/headers/constants.h"

MESSAGE * parse_from_bytes(char * buffer){

    MESSAGE * new = calloc(1, sizeof(MESSAGE));

    memcpy(&(new->checksum), buffer, 2);
    memcpy(&(new->message_type), buffer+2, 1);
    memcpy(&(new->flags), buffer+3, 1);

    if (new->message_type != NO_DATA && new->flags.message_id == 1){
        memcpy(&(new->data_length), buffer+4, 2);
        memcpy(&(new->message_stream_id), buffer+6, 2);
        memcpy(&(new->sequence_number), buffer+8, 4);
        memcpy(&(new->sequence_number), buffer+12, 4);
        new->data = calloc(new->data_length, sizeof(char));
        memcpy(new->data, buffer+16, new->data_length);
    }
    else if(new->message_type != NO_DATA && new->flags.message_id == 0){
        memcpy(&(new->data_length), buffer+4, 2);
        memcpy(new->data, buffer+6, new->data_length);

    }

    return new;
}

char * parse_to_bytes(MESSAGE * msg){

    char * bytes = calloc(16 + msg->data_length, sizeof(char));

    memcpy(bytes, &(msg->checksum), 2);
    memcpy(bytes+2, &(msg->message_type), 1);
    memcpy(bytes+3, &(msg->flags), 1);

    if(msg->message_type != NO_DATA && msg->flags.message_id == 1){
        memcpy(bytes+4, &(msg->data_length), 2);
        memcpy(bytes+6, &(msg->message_stream_id), 2);
        memcpy(bytes+8, &(msg->sequence_number), 4);
        memcpy(bytes+12, &(msg->fragment_count), 4);
        memcpy(bytes+16, msg->data, msg->data_length);
    }
    else if (msg->message_type != NO_DATA && msg->flags.message_id == 0){
        memcpy(bytes+4, &(msg->data_length), 2);
        memcpy(bytes+6, msg->data, msg->data_length);
    }

    return bytes;
}