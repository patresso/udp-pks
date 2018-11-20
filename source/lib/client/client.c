#include "headers/client.h"
#include "../common/misc/headers/messages.h"
#include "../common/misc/headers/constants.h"


void client(in_addr_t addr, int port){


    


    struct sockaddr_in servaddr;
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);    

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = addr;
    servaddr.sin_port = htons(port);

    sendto(sockfd, "Hellou from client!", 21, 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    print_message(INFO, "Hellou message sent");

    int n, len;
    char * buffer = calloc(sizeof(char), 1024);
    n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*) &servaddr, &len);
    buffer[n] = '\0';

    print_message(SERVER, buffer);

    print_message(INFO, "Stopping Client");
    close(sockfd);

    return;

}