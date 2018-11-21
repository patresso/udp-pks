#include "headers/connection_threads.h"
#include "../misc/headers/constants.h"
#include "../misc/headers/messages.h"
#include "../protocol/headers/definitions.h"
#include "headers/recieve.h"
#include "headers/message_processing.h"
#include "headers/send.h"
#include "../file_handling/headers/recievefile.h"
#include "../file_handling/headers/sendfile.h"

void * serverside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    print_message(OK, "Server started");
    print_message(INFO, "Waiting for connection");

    MESSAGE * message;
    args->conn_state = NOT_CONNECTED;
    //main cycle
    while(args->flag == RUN){

        //recieve message
        message = recieve(args);

        //protocol
        if (args->conn_state == CONNECTED){
            
            //chat
            if (message->message_type == ASCII){
                print_message(CLIENT, message->data);
            }
            else if (message->flags.stream_income == 1 && args->cmd != SEND_FILE){
                //start recieving a file
                print_message(INFO, "Recieving a file");
                sendmessage(create_message(STRIN|ACK, NO_DATA, 0, 0, 0, NULL, 0), args);
                recievefile(message, args);
                print_message(OK, "Download complete");
            }
            else if (args->cmd == SEND_FILE && message->flags.stream_income == 1 && message->flags.ack == 1){
                print_message(INFO, "Sending a file");
                sendfile(message, args);
                print_message(OK, "File sent");
                args->cmd = NO_VAL;
            }

        }

        if (args->conn_state == NOT_CONNECTED && message->flags.start == 1){
            sendmessage(create_message((ACK), NO_DATA, 0, 0, 0, NULL, 0), args);
            message = recieve(args);
            if (message->flags.ack == 1){
                print_message(OK, "Connected");
                args->conn_state = CONNECTED;
            }
            else{
                print_message(FAIL, "Connection fail");
            }
        }

    }   

    pthread_exit(0);
}

void * clientside_communication(void * arg){
    /*THREAD*/
    THREAD_ARGS * args = (THREAD_ARGS*)arg;
    print_message(OK, "Client started");

    int err_count = 0;

    MESSAGE * message;
    while (args->flag == RUN){
        
        if (err_count == 3){
            print_message(FAIL, "3. attemp failed, exiting");
            exit(EXIT_FAILURE);
        }

        if (args->conn_state == NOT_CONNECTED){
            print_message(INFO, "Trying to connect");
            sendmessage(create_message(START, NO_DATA, 0, 0, 0, NULL, 0), args);
            message = recieve(args);
            if (message->flags.ack == 1){
                sendmessage(create_message(START|ACK, NO_DATA, 0, 0, 0, NULL, 0), args);
                print_message(OK, "Connected");
                args->conn_state = CONNECTED;
                err_count = 0;
            }
            else{
                err_count++;
            }
        }

        //protocol
        if (args->conn_state == CONNECTED){
            //recieve message
            message = recieve(args);

            //chat
            if (message->message_type == ASCII){
                print_message(SERVER, message->data);
            }
            else if (message->flags.stream_income == 1 && args->cmd != SEND_FILE){
                //start recieving a file
                print_message(INFO, "Recieving a file");
                sendmessage(create_message(STRIN|ACK, NO_DATA, 0, 0, 0, NULL, 0), args);
                // recievefile(message);
                print_message(OK, "Download complete");
            }
             else if (args->cmd == SEND_FILE && message->flags.stream_income == 1 && message->flags.ack == 1){
                print_message(INFO, "Sending a file");
                sendfile(message, args);
                print_message(OK, "File sent");
                args->cmd = NO_VAL;
            }

        }

    }

    pthread_exit(0);
}