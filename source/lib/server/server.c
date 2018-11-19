#include "headers/server.h"
#include "../common/misc/headers/messages.h"
#include "../common/misc/headers/constants.h"

void server(int port){

    //bind and listen for start message
    //send start ack
    //wait for start ack

    //async wait for new messages
    //be able to send
    //if incoming message block ability to send
    //TODO:

    struct sockaddr_in servaddr, cliaddr; 
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    bind(sockfd, (const struct sockaddr*) &servaddr, sizeof(servaddr));

    int n, len;
    char * buffer = calloc(sizeof(char), 1024);
    n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*) &cliaddr, &len);

    buffer[n] = '\0';

    print_message(CLIENT, buffer);

    sendto(sockfd, "Thank you for your message! Bye.", 34, 0, (const struct sockaddr*)&cliaddr, sizeof(cliaddr));

    print_message(INFO, "Hellou message sent");
    print_message(INFO, "Stopping server");
    close(sockfd);

    return;

}