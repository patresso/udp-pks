#include "headers/intro.h"

int intro(){

    printf("Hello user, please choose your side:\n[server/client]");
    char * answer = (char*)malloc(7*sizeof(char));
    scanf("%s", answer);

    int type;
    if (strcmp(answer, "server") == 0)        
        type = SERVER_SIDE;
    else if (strcmp(answer, "client") == 0) 
        type = CLIENT_SIDE;
    else{
        printf("%s is not an option!\n", answer);
        type = NO_VAL;
    }

    free(answer);
    return type;
}
