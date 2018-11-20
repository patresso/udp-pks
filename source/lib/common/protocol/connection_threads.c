#include "headers/connection_threads.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "../protocol/headers/definitions.h"
#include "headers/recieve.h"
#include "headers/message_processing.h"
#include "headers/send.h"

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
            message = create_message(0, ASCII, 0, 0, 0, args->data, strlen(args->data));
            sendmessage(message, args);
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

    MESSAGE * message;
    while (args->flag == RUN){
        
        message = recieve(args);
        print_message(SERVER, message->data);

        if (args->cmd == CHAT){
            //establish chat
            // message = create_message(0, ASCII, 0, 0, 0, args->data, strlen(args->data));
            // sendmessage(message, args);
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