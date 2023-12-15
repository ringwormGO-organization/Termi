#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201

void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void str_overwrite_stdout() 
{
    printf("\r%s", "> ");
    fflush(stdout);
}

void str_trim_lf(char* arr, int length) {
    int i;
    for (i = 0; i < length; i++) { // trim \n
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

bool str_to_uint16(const char *str, uint16_t *res) {
    char *end;
    errno = 0;
    long val = strtol(str, &end, 10);
    if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000) {
        return false;
    }
    *res = (uint16_t)val;
    return true;
}

/* ------------------------------------ */

volatile sig_atomic_t flag = 0;
int sockfd = 0;
char nickname[LENGTH_NAME];

void catch_ctrl_c_and_exit(int sig) 
{
    flag = sig;

    printf("Bye\n");
    exit(sig);
}

void* recv_msg_handler() 
{
    char receiveMessage[LENGTH_SEND];
    while (1) 
    {
        int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);

        if (receive > 0) 
        {
            printf("\r%s", receiveMessage);
            str_overwrite_stdout();
        } 
        
        else if (receive == 0) 
        {
            break;
        } 
        
        else 
        { 
            // -1 
        }
    }

    return NULL;
}

void* send_msg_handler() 
{
    char message[LENGTH_MSG];
    while (1) 
    {
        str_overwrite_stdout();
        while (fgets(message, LENGTH_MSG, stdin) != NULL) 
        {
            str_trim_lf(message, LENGTH_MSG);

            if (strlen(message) == 0) 
            {
                str_overwrite_stdout();
            } 
            
            else 
            {
                break;
            }
        }

        send(sockfd, message, LENGTH_MSG, 0);

        if (strcmp(message, "exit") == 0) 
        {
            break;
        }
    }

    catch_ctrl_c_and_exit(2);
    return NULL;
}

int main()
{
    char ip[1024];
    char temp_port[1024];

    uint16_t port = 0;

    signal(SIGINT, catch_ctrl_c_and_exit);

    printf("Termi client\n");

    /* User specified informations */
    printf("Enter server IP: ");
    scanf("%1023s", ip);

    printf("Enter server port: ");
    scanf("%1023s", temp_port);

    bool conv_result = str_to_uint16(temp_port, &port);
    if (conv_result == false)
    {
        printf("Error converting port from string to uint16_t!\n");
        exit(EXIT_FAILURE);
    }

    clear_input_buffer();
    printf("Please enter your name: ");

    if (fgets(nickname, LENGTH_NAME, stdin) != NULL) 
    {
        str_trim_lf(nickname, LENGTH_NAME);
    }

    if (strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME - 1) 
    {
        printf("\nName must be more than one and less than thirty characters.\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");

    /* Create socket */
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) 
    {
        printf("Fail to create a socket.");
        exit(EXIT_FAILURE);
    }

    /* Socket information */
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = inet_addr(ip);
    server_info.sin_port = htons(port);

    /* Connect to server */
    int err = connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    if (err == -1) 
    {
        printf("Connection to Server error!\n");
        exit(EXIT_FAILURE);
    }
    
    /* Names */
    getsockname(sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
    getpeername(sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("You are: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    printf("\n");

    send(sockfd, nickname, LENGTH_NAME, 0);

    pthread_t send_msg_thread;
    if (pthread_create(&send_msg_thread, NULL, reinterpret_cast<void* (*)(void*)>(send_msg_handler), NULL) != 0) 
    {
        printf("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    pthread_t recv_msg_thread;
    if (pthread_create(&recv_msg_thread, NULL, reinterpret_cast<void* (*)(void*)>(recv_msg_handler), NULL) != 0) 
    {
        printf("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    while (1) 
    {
        if (flag) 
        {
            printf("\nBye\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
