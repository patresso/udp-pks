#include "headers/crc.h"
#include "../protocol/headers/definitions.h"
#include "headers/constants.h"

unsigned short crc16(const unsigned char* data_p, unsigned char length){
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (length--){
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    return crc;
}

int check_integrity(MESSAGE * message){

    unsigned short crc = crc16(message->data, message->data_length);
    if (crc != message->checksum){
        return BROKEN;
    }

    return OK;
}