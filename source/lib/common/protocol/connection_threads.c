#include "headers/connection_threads.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "../protocol/headers/definitions.h"
#include "headers/recieve.h"

void * serverside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    print_message(OK, "Server started");

    MESSAGE * message;
    char * text;
    //main cycle
    while(args->flag == RUN){

        //recieve message and print it
        message = recieve(args);
        print_message(CLIENT, message->data);

        if (args->cmd == CHAT){
            //establish chat
            //propably just sendthis text to other side
            print_message(INFO, "should start chat");
            args->cmd = NO_VAL;
        }
        else if (args->cmd == SEND_FILE){
            //send file
            print_message(INFO, "should send a file");
            args->cmd = NO_VAL;
        }

    }   

    pthread_exit(0);
}

void * clientside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    print_message(OK, "Client started");

    while (args->flag == RUN){
        
        if (args->cmd == CHAT){
            //establish chat
            //just send the data to the other side
            args->cmd = NO_VAL;
        }
        else if (args->cmd == SEND_FILE){
            //send file
            print_message(INFO, "should send a file");
            args->cmd = NO_VAL;
        }
        

    }

    pthread_exit(0);
}