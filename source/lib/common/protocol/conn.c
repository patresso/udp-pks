#include "headers/conn.h"
#include "headers/actions.h"
#include "headers/headers.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "headers/send_recieve.h"

void * serverside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    HEADER_FULL * msg;
    print_message(OK, "Server started");
    
    int conn = NO_VAL;
    //main cycle
    while(args->flag == RUN){

        // if (conn != OK){
        //     conn = wait_for_connection(args);
        //     if (conn == OK)
        //         print_message(INFO, "Connection established");
        //     else
        //         print_message(FAIL, "Communication error");
        // }
        
        msg = recieve_message(args);

        print_message(CLIENT, msg->data);

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

        //3x 3s
        // establish_connection(args);

        
        if (args->cmd == CHAT){
            //establish chat
            print_message(INFO, "should start chat");
            HEADER_FULL * msg = convert_to_text_message(args->data);
            send_message(args, msg , CLIENT);
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