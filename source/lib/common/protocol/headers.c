#include "headers/headers.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/crc.h"

//funkcie nad mojimi hlavickami 
HEADER_FULL * parse_message_from_bytes(void * data){
    HEADER_FULL * msg = calloc(1, sizeof(HEADER_FULL));
    
    msg->checksum = *(u_int16_t*)(data);
    msg->message_type = *(u_int8_t*)(data+2);
    msg->flags = *(FLAGS*)(data+3);
    
    if (msg->message_type != NO_DATA && msg->flags.message_id == 0){
        msg->data_length = *(u_int16_t*)(data+4);
        msg->data = (char*)data+6;
    }
    else if (msg->message_type != NO_DATA && msg->flags.message_id == 1 ){
        msg->data_length = *(u_int16_t*)(data+4);
        msg->message_stream_id = *(u_int16_t*)(data+6);
        msg->sequence_number = *(u_int32_t*)(data+8);
        msg->fragment_count = *(u_int32_t*)(data+12);
        msg->data = (char*)data+16;
    }
    else{
        //is a no data message
    }


    return msg;

}

HEADER_FULL * text_to_message(void * data){
    HEADER_FULL * msg = calloc(1, sizeof(HEADER_FULL));

    msg->checksum = 0;
    msg->data = (char*)data;
    msg->message_type = ASCII;
    msg->data_length = strlen(data);

    //TODO: not done

    return msg;
}

unsigned char * convert_to_bytes(HEADER_FULL * msg){
    char * bytes = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);

    *(u_int16_t*)bytes = msg->checksum;
    *(u_int8_t*)(bytes+2) = msg->message_type;
    *(FLAGS*)(bytes+3) = msg->flags;
    *(u_int16_t*)(bytes+4) = msg->data_length;
    memcpy((void*)(bytes+6), msg->data, msg->data_length);

    return bytes;
}