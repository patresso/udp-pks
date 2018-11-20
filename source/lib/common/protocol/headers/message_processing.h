#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "definitions.h"

MESSAGE * parse_from_bytes(char * buffer);
char * parse_to_bytes(MESSAGE * msg);
MESSAGE * create_message(u_int8_t flags, int message_type, int stream_id, int sequence_number, int fragment_count, char * data, int data_length);