#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef HEADERS_H
#define HEADERS_H

typedef struct {
    u_int8_t start:1;
    u_int8_t ack:1;
    u_int8_t finnish:1;
    u_int8_t message_id:1;
    u_int8_t stream_income:1;
    u_int8_t resend:1;
    u_int8_t stream_end:1;
}FLAGS;

typedef struct header_full{
    u_int16_t checksum;
    u_int8_t message_type;
    FLAGS flags;
    u_int16_t data_length;
    u_int16_t message_stream_id;
    u_int32_t sequence_number;
    u_int32_t fragment_count;
    char * data;
}HEADER_FULL;

typedef struct header_single_msg{
    u_int16_t checksum;
    u_int8_t message_type;
    FLAGS flags;
    u_int16_t data_length;
    char * data;
}HEADER_SINGLE_MSG;

typedef struct header_no_msg{
    u_int16_t checksum;
    u_int8_t message_type;
    FLAGS flags;
}HEADER_NO_MSG;

typedef struct thread_args{
    int sockfd;
    struct sockaddr_in * serveraddr;
    struct sockaddr_in * clientaddr;
    int flag;
    int cmd;
    char * data;
}THREAD_ARGS;   

#endif