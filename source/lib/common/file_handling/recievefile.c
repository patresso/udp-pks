#include "headers/recievefile.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "../protocol/headers/definitions.h"
#include "../protocol/headers/recieve.h"
#include "../protocol/headers/message_processing.h"
#include "../protocol/headers/send.h"

int recievefile(MESSAGE * message, THREAD_ARGS * args){

    FILE_INFORMATION info;
    
    //first message is fragment size
    info.fragment_size = atoi(message->data);

    //filename fragments
    message = recieve(args);
    char * filename = calloc((info.fragment_size+1)*message->fragment_count, sizeof(char));
    memcpy(filename, message->data, message->data_length);

    for (int i = 1; i < message->fragment_count; i++){
        message = recieve(args);
        memcpy(filename+(i*info.fragment_size), message->data, message->data_length);
    }
    
    //data fragments

    FRAGMENT * first = calloc(1, sizeof(FRAGMENT));
    message = recieve(args);
    first->message = message;
    first->fragments[0] = 0;
    first->fragments[1] = 0;
    first->next = NULL;
    FRAGMENT * iterator = first;

    for (int i = 1; i < message->fragment_count; i++){
        message = recieve(args);
        iterator->next = calloc(1, sizeof(FRAGMENT));
        iterator = iterator->next;
        iterator->message = message;
        iterator->fragments[0] = i;
        iterator->fragments[1] = i;
        iterator->next = NULL;
    }

    //open file
    char * filename_full = calloc(255, sizeof(char));
    sprintf(filename_full, "./downloads/%s", filename);
    FILE * fd = fopen(filename_full, "wb");
    if (fd == NULL) {
        print_message(FAIL, "Could not create file");
        return 1;
    }

    //simple assemly of ok fragments
    iterator = first;
    int i = 0;
    while(iterator != NULL){
        fwrite(iterator->message->data, 1, iterator->message->data_length, fd);
        iterator = iterator->next;
    }

    fflush(fd);
    fclose(fd);

    //free
        //all messages


    return OK;
}