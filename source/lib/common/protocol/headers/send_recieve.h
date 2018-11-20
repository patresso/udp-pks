#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "headers.h"

HEADER_FULL * recieve_message(THREAD_ARGS * args, int side);
int send_message(THREAD_ARGS * args, HEADER_FULL * msg, int side);