#include "headers/intro.h"
#include "../protocol/headers/definitions.h"

int intro(){

    printf("Hello user, please choose your side:\n[server/client]");
    char * answer = (char*)malloc(7*sizeof(char));
    scanf("%s", answer);

    int type;
    if (strcmp(answer, "server") == 0)        
        type = SERVER_SIDE;
    else if (strcmp(answer, "client") == 0) 
        type = CLIENT_SIDE;
    else{
        printf("%s is not an option!\n", answer);
        type = NO_VAL;
    }

    free(answer);
    return type;
}

int ask_for_port(void){

    printf("Select a port: [1024-50000]\n");
    int port;
    scanf("%d", &port);

    return port;
}

in_addr_t ask_for_addr(void){

    printf("Type ip addres to connect to (in dot notation): [X.X.X.X]\n");
    char address[16];
    scanf("%s", address);
    in_addr_t addr = inet_addr(address);

    return addr;
}

char * ask_for_fragment_size(THREAD_ARGS * args){

    printf("Type max fragment size: [1 - 1400]\n");
    int size;
    scanf("%d", &size);
    args->frag_size = size;
    char * size_buf = calloc(20, sizeof(char));
    sprintf(size_buf, "%d", size);

    return size_buf;
}

char * ask_for_filename(void){

    printf("Filename:\n");
    char * filename = calloc(255, sizeof(char));
    scanf("%s", filename);

    return filename;
}

int ask_for_num_of_broken(void){

    printf("Number of broken messages:\n");
    int x;
    scanf("%d", &x);

    return x;
}