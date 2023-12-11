/**
 * @author Chenxu Wang, Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT license
 * DESCRIPTION: Client file
 */

#include "client.hpp"

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

void* recv_msg_handler()
{
    char receiveMessage[LENGTH_SEND];
    while (1) 
    {
        int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);

        if (receive > 0) 
        {
            printf("\r%s\n", receiveMessage);
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

    return NULL;
}
