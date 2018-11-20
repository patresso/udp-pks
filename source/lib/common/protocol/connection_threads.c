#include "headers/connection_threads.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "../protocol/headers/definitions.h"

void * serverside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    MESSAGE * msg;
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
        
        msg = recieve_message(args, SERVER);

        print_message(CLIENT, msg->data);

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