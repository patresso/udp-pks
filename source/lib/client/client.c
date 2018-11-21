#include "headers/client.h"
#include "../common/misc/headers/messages.h"
#include "../common/misc/headers/constants.h"
#include "../common/misc/headers/control.h"
#include "../common/protocol/headers/connection_threads.h"
#include "../common/protocol/headers/definitions.h"
#include "../common/protocol/headers/message_processing.h"
#include "../common/protocol/headers/send.h"
#include "../common/misc/headers/intro.h"

void client(in_addr_t addr, int port){

    struct sockaddr_in servaddr;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) handle_error("File descriptor unavailable");
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = addr;
    servaddr.sin_port = htons(port);

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    THREAD_ARGS * args = (THREAD_ARGS*)malloc(sizeof(THREAD_ARGS)); 
    args->sockfd = sockfd;
    args->address = &servaddr;
    args->flag = RUN;
    args->cmd = NO_VAL;
    args->conn_state = NOT_CONNECTED;

    pthread_create(&tid, &attr, clientside_communication, args); 

    int op;
    char * text = calloc(sizeof(char), DEFAULT_FRAGMENT_MAX_SIZE);
    fgets(text, 5, stdin);  //for triailing newlines
    MESSAGE * message;
    for (op = NO_VAL; ; op = ask_for_operation(text)){
        if (op == NO_VAL) continue;
        switch (op){
            case QUIT:          //send closing message
                                print_message(INFO, "Shutting down client");
                                args->flag = QUIT;
                                pthread_cancel(tid);
                                close(sockfd);
                                exit(EXIT_SUCCESS);

            case DISCONNECT:    print_message(INFO, "Not yet implemented");
                                //send closing message
                                //do all closings
                                //goto up
                                break;

            case STATISTICS:    print_message(INFO, "Not yet implemented");
                                break;

            case SERVER_INFO:   //print server info, addr, etc.
                                print_message(INFO, "Not yet implemented");
                                break;
            
            case CHAT:          //establish chat
                                if (args->conn_state == NOT_CONNECTED){
                                    print_message(FAIL, "Not connected");
                                    break;
                                }
                                message = create_message(0, ASCII, 0, 0, 0, text, strlen(text));
                                sendmessage(message, args);
                                break;
            
            case SEND_FILE:     //send a file to server
                                if (args->conn_state == NOT_CONNECTED){
                                    print_message(FAIL, "Not connected");
                                    break;
                                }
                                char * filename = ask_for_filename();
                                char * fragsize = ask_for_fragment_size(args);
                                fgets(text, 10, stdin);
                                sendmessage(create_message(STRIN, FRAG_SIZE, 0, 0, 0, fragsize, strlen(fragsize)), args);
                                args->data = filename;
                                args->cmd = SEND_FILE;
                                break;
        
        }   
    }

    return;

}