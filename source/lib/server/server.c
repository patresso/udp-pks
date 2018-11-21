#include "headers/server.h"
#include "../common/misc/headers/messages.h"
#include "../common/misc/headers/constants.h"
#include "../common/misc/headers/control.h"
#include "../common/protocol/headers/connection_threads.h"
#include "../common/protocol/headers/definitions.h"
#include "../common/protocol/headers/message_processing.h"
#include "../common/protocol/headers/send.h"
#include "../common/protocol/headers/recieve.h"
#include "../common/misc/headers/intro.h"

void server(int port){


    struct sockaddr_in servaddr, cliaddr; 

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) handle_error("File descriptor unavailable");
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    bind(sockfd, (const struct sockaddr*) &servaddr, sizeof(servaddr));
    if (bind < 0) handle_error("Socket already in use");

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    THREAD_ARGS * args = (THREAD_ARGS*)malloc(sizeof(THREAD_ARGS)); 
    args->sockfd = sockfd;
    args->address = &cliaddr;
    args->flag = RUN;
    args->cmd = NO_VAL;
    args->conn_state = NOT_CONNECTED;

    //work on this thread
    pthread_create(&tid, &attr, serverside_communication, args);
    char * filename;
    char * fragsize;
    int op;
    char * text = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);
    fgets(text, 5, stdin);  //for triailing newlines
    MESSAGE * message;
    for (op = NO_VAL; ; op = ask_for_operation(text)){
        if (op == NO_VAL) continue;
        switch (op){
            case QUIT:          //send closing message
                                print_message(INFO, "Shutting down server");
                                args->flag = QUIT;
                                pthread_cancel(tid);
                                close(sockfd);
                                exit(EXIT_SUCCESS);

            case DISCONNECT:    print_message(INFO, "Not yet implemented");
                                //send closing message
                                sendmessage(create_message(FIN, NO_DATA, 0, 0, 0, NULL, 0), args);
                                args->cmd = DISCONNECT;
                                break;

            case STATISTICS:    print_message(INFO, "Not yet implemented");
                                break;

            case CLIENT_INFO:        //print client info, addr, etc.
                                print_message(INFO, "Not yet implemented");
                                break;
            
            case SEND_FILE:     //send a file to client
                                if (args->conn_state == NOT_CONNECTED){
                                    print_message(FAIL, "Not connected");
                                    break;
                                }
                                filename = ask_for_filename();
                                fragsize = ask_for_fragment_size(args);
                                fgets(text, 10, stdin);
                                sendmessage(create_message(STRIN, FRAG_SIZE, 0, 0, 0, fragsize, strlen(fragsize)), args);
                                args->data = filename;
                                args->num_of_broken_messages = 0;
                                args->cmd = SEND_FILE;
                                break;

            case CHAT:          //establish chat
                                if (args->conn_state == NOT_CONNECTED){
                                    print_message(FAIL, "Not connected");
                                    break;
                                }
                                sendmessage(create_message(0, ASCII, 0, 0, 0, text, strlen(text)), args);
                                break;

            case SEND_FILE_BR:  if (args->conn_state == NOT_CONNECTED){
                                    print_message(FAIL, "Not connected");
                                    break;
                                }
                                filename = ask_for_filename();
                                fragsize = ask_for_fragment_size(args);
                                args->num_of_broken_messages = ask_for_num_of_broken();
                                fgets(text, 10, stdin);
                                sendmessage(create_message(STRIN, FRAG_SIZE, 0, 0, 0, fragsize, strlen(fragsize)), args);
                                args->data = filename;
                                args->cmd = SEND_FILE;
                                break;
        
        }   
    }


    return;

}



    