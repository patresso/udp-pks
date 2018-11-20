#include "headers/client.h"
#include "../common/misc/headers/messages.h"
#include "../common/misc/headers/constants.h"
#include "../common/protocol/headers/actions.h"
#include "../common/misc/headers/control.h"
#include "../common/protocol/headers/conn.h"
#include "../common/protocol/headers/headers.h"


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
    args->serveraddr = &servaddr;
    args->flag = RUN;
    args->cmd = NO_VAL;

    pthread_create(&tid, &attr, clientside_communication, args); 

    int op;
    for (op = NO_VAL; ; op = ask_for_operation()){
        if (op == NO_VAL) continue;
        switch (op){
            case QUIT:          //send closing message
                                print_message(INFO, "Shutting down server");
                                args->flag = QUIT;
                                pthread_join(tid, NULL);
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
                                args->cmd = CHAT;
                                break;
            
            case SEND_FILE:     //send a file to client
                                args->cmd = SEND_FILE;
                                break;

        
        }   
    }

    return;

}