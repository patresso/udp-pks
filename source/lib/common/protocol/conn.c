#include "headers/conn.h"
#include "headers/actions.h"
#include "headers/headers.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"

void * serverside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    print_message(OK, "Server started");
    
    int conn = NO_VAL;
    //main cycle
    while(args->flag == RUN){

        if (conn != OK){
            conn = wait_for_connection(args);
            if (conn == OK)
                print_message(INFO, "Connection established");
            else
                print_message(FAIL, "Communication error");
        }

        if (args->cmd == CHAT){
            //establish chat
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

        //TODO: try to connect 3x for 3 seconds and quit

        if (args->cmd == CHAT){
            //establish chat
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