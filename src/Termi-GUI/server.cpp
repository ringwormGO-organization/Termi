/**
 * @author Chenxu Wang, Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT license
 * DESCRIPTION: Server file
 */

#include "server.hpp"

#ifdef _WIN32
#elif __linux__ || __FreeBSD__ || __OpenBSD__ || __NetBSD__
ClientList* root;

std::string client_input = "";
std::mutex client_input_mutex;

ClientList* newNode(int sockfd, char* ip)
{
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );
    np->data = sockfd;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);
    strncpy(np->name, "NULL", 5);
    return np;
}

void polish_str(char *str)
{
    int len = strlen(str);
    int tail = 0;

    for (int i = 0; i < len; ++i) {
        if (str[i] != '\t') {
            str[tail++] = str[i];
        }
    }

    // Check if the string ends with '\n', and if not, add it
    if (tail == 0 || str[tail - 1] != '\n') {
        str[tail++] = '\n';
    }

    // Null-terminate the result string
    str[tail] = '\0';
}

char* trim_whitespace(char* str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( frontp != str && endp == frontp )
            *str = '\0';
    else if( str + len - 1 != endp )
            *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
        while( *frontp ) { *endp++ = *frontp++; }
        *endp = '\0';
    }

    return str;
}

/* ------------------------------------ */

void send_to_all_clients(const char* fmt, ...) 
{
    ClientList *tmp = root->link;

    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    buf[sizeof(buf) - 1] = 0;
    va_end(args);

    while (tmp != NULL) 
    {
        polish_str(buf);

        printf("Send to sockfd %d: %s", tmp->data, buf);
        send(tmp->data, buf, LENGTH_SEND, 0);

        tmp = tmp->link;
    }
}

void* client_handler(void* client_arg)
{
    ClientArg *args = (ClientArg *)client_arg;

    int leave_flag = 0;
    char nickname[LENGTH_NAME];
    char recv_buffer[LENGTH_MSG];
    char send_buffer[LENGTH_SEND];
    ClientList *np = (ClientList *)args->p_client;

    /* Naming */
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME - 1) 
    {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } 
    
    else 
    {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s (%s)(%d) joined!\n\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s (%s)!\n", np->name, np->ip);
        send_to_all_clients(send_buffer);
    }

    sprintf(send_buffer, "Termi> %s\n");
    send_to_all_clients(send_buffer);

    // Conversation
    while (1) 
    {
        if (leave_flag) 
        {
            break;
        }

        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0) 
        {
            if (strlen(recv_buffer) == 0) 
            {
                continue;
            }

            sprintf(send_buffer, "%s:%s from %s\n", np->name, recv_buffer, np->ip);

            /* Lock the mutex before accessing */
            std::unique_lock<std::mutex> lock(client_input_mutex);

            client_input = recv_buffer;

            /* Unlock the mutex when done */
            lock.unlock();
        } 
        
        else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) 
        {
            printf("%s(%s)(%d) left!\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) left!\n", np->name, np->ip);
            leave_flag = 1;
        } 
        
        else 
        {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }

        send_to_all_clients(send_buffer);
    }

    /* Remove node */
    close(np->data);

    /* Remove an edge node */
    if (np == args->now) 
    {
        args->now = np->prev;
        args->now->link = NULL;
    } 
    
    /* Remove a middle node */
    else 
    {
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }

    free(np);
    return NULL;
}
#endif
