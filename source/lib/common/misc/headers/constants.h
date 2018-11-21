#define ERR -1
#define NO_VAL -1

#define SERVER_SIDE 0
#define CLIENT_SIDE 1

//message codes
#define OK 0
#define INFO 1
#define FAIL 2
#define SERVER 3
#define CLIENT 4

//color codes
#define RESET "\033[0m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;36m"
#define RED "\033[0;31m"

//defaults
#define DEFAULT_FRAGMENT_MAX_SIZE 1400

//operation constants
#define QUIT 0
#define DISCONNECT 1
#define CLIENT_INFO 2
#define STATISTICS 3
#define CHAT 4
#define SEND_FILE 5
#define SERVER_INFO 6

//thread manipulation
#define RUN 1

//header constants
    //message types
#define NO_DATA 0
#define BINARY 1
#define ASCII 2
#define FILE_INFO 3

//flags
#define START   0b10000000
#define ACK     0b01000000
#define FIN     0b00100000
#define MSGID   0b00010000
#define STRIN   0b00001000
#define RESEND  0b00000100
#define END     0b00000010

//connection states
#define NOT_CONNECTED 0
#define CONNECTED     1
