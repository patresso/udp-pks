#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef struct {
    u_int8_t start:1;
    u_int8_t ack:1;
    u_int8_t finnish:1;
    u_int8_t message_id:1;
    u_int8_t stream_income:1;
    u_int8_t resend:1;
    u_int8_t stream_end:1;
}FLAGS;

typedef struct message{
    u_int16_t checksum;
    u_int8_t message_type;
    FLAGS flags;
    u_int16_t data_length;
    u_int16_t message_stream_id;
    u_int32_t sequence_number;
    u_int32_t fragment_count;
    char * data;
}MESSAGE;

typedef struct broken_list{
    MESSAGE * message;
    struct broken_list * next;
}BROKEN_LIST;

typedef struct thread_args{
    int sockfd;
    struct sockaddr_in * address;
    int flag;
    int cmd;
    char * data;
    int conn_state;
    int frag_size;
    BROKEN_LIST * broken;
    int num_of_broken_messages;
}THREAD_ARGS;

typedef struct file_info{
    u_int32_t size;
    char * filename;
    u_int32_t fragment_size;
}FILE_INFORMATION;

typedef struct fragment{
    int fragments[2];
    MESSAGE * message;
    struct fragment * next;
}FRAGMENT;

#endif