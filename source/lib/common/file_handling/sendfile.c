#include "headers/sendfile.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "../protocol/headers/definitions.h"
#include "../protocol/headers/recieve.h"
#include "../protocol/headers/message_processing.h"
#include "../protocol/headers/send.h"

int sendfile(MESSAGE * message, THREAD_ARGS * args){

    //load file
    char * filename = calloc(255, sizeof(char));
    sprintf(filename, "./public/%s", args->data);
    FILE * fd = fopen(filename, "rb");
    if (fd == NULL) {
        print_message(FAIL, "No such file");
        return 1;
    }

    int file_len;
    fseek(fd, 0, SEEK_END);
    file_len = ftell(fd);
    rewind(fd);
    
    char * buffer = (char *)malloc((file_len+1)*sizeof(char));
    fread(buffer, file_len, 1, fd);
    fclose(fd); 

    //number of fragments
    int frag_count = (file_len / args->frag_size)+1;
    // if ((file_len % args->frag_size) != 0) frag_count += 1;

    int filename_fragment_count = (strlen(args->data) / args->frag_size);
    if ((strlen(args->data) % args->frag_size) != 0) filename_fragment_count += 1;
    

    //process file to send
        // make fragments into linked list
    char * fragment_buffer = calloc(args->frag_size+1, sizeof(char));
    memcpy(fragment_buffer, buffer, args->frag_size);

    FRAGMENT * first = calloc(1, sizeof(FRAGMENT));
    first->message = create_message(MSGID, BINARY, 1, 0, frag_count, fragment_buffer, (frag_count > 1)?(args->frag_size):(file_len%args->frag_size) );
    FRAGMENT * iterator = first;

    for (int i = 1; i < frag_count; i++){
        iterator->next = calloc(1, sizeof(FRAGMENT));
        iterator = iterator->next;
        memcpy(fragment_buffer, buffer+(i*args->frag_size), args->frag_size);
        iterator->message = create_message(MSGID, BINARY, 1, i, frag_count, fragment_buffer, (i+1 == frag_count)?(file_len%args->frag_size):(args->frag_size) );
    }
    iterator->next == NULL;

    //process filename
    FRAGMENT * first_filename = calloc(1, sizeof(FRAGMENT));
    memcpy(fragment_buffer, args->data, args->frag_size);
    first_filename->message = create_message(MSGID, FILENAME, 1, 0, filename_fragment_count, fragment_buffer, strlen(fragment_buffer));
    iterator = first_filename;
    
    for (int i = 1; i < filename_fragment_count; i++){
        iterator->next = calloc(1, sizeof(FRAGMENT));
        iterator = iterator->next;
        memcpy(fragment_buffer, args->data+(i*args->frag_size), args->frag_size);
        iterator->message = create_message(MSGID, FILENAME, 1, i, filename_fragment_count, fragment_buffer, strlen(fragment_buffer));
    }
    iterator->next = NULL;

    sleep(1);

    //send filename
    iterator = first_filename;
    while (iterator != NULL){
        usleep(1000);
        sendmessage(iterator->message, args);
        iterator = iterator->next;
    }

    //send file
    iterator = first;
    while (iterator != NULL){
        usleep(800);
        sendmessage(iterator->message, args);
        iterator = iterator->next;
    }

    //place for resend mechanism
    message = recieve(args);
    iterator = first;
    while (message->flags.stream_end == 0 && message->flags.ack == 0){
        //could be only resend message
        while (iterator->message->sequence_number != message->sequence_number){
            iterator = iterator->next;
        }
        sendmessage(iterator->message, args);
        message = recieve(args);
    }


    free(filename);
    free(buffer);
    free(fragment_buffer);

    return OK;
}