#include "headers/messages.h"
#include "headers/constants.h"

void print_message(int type, char * messsage){
    
    switch (type){

        case OK:        printf("[ %sOK%s ]", GREEN, RESET);
                        break;
        case FAIL:      printf("[%sfail%s]", RED, RESET);
                        break;
        case INFO:      printf("[%sinfo%s]", BLUE, RESET);
                        break;
        case CLIENT:    printf("[%sclient%s]", BLUE, RESET);
                        break;
        case SERVER:    printf("[%sserver%s]", BLUE, RESET);
                        break;
    }

    printf("%s\n", messsage);
    return;
}

void handle_error(char * message){
    print_message(FAIL, message);
    exit(EXIT_FAILURE);
}