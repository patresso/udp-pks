#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "constants.h"
#include "../../protocol/headers/definitions.h"

int intro(void);
int ask_for_port(void);
in_addr_t ask_for_addr(void);
char * ask_for_fragment_size(THREAD_ARGS * args);
char * ask_for_filename(void);
int ask_for_num_of_broken(void);