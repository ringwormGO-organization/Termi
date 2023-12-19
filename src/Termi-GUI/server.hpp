/**
 * @author Chenxu Wang, Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT license
 * DESCRIPTION: Server header file
 */

#pragma once

#include <iostream>
#include <string>
#include <mutex>

/* Client input is copied here so it is visible from thread where console is drawn */
extern std::string client_input;
extern std::mutex client_input_mutex;

#ifdef _WIN32
#elif __linux__ || __FreeBSD__ || __OpenBSD__ || __NetBSD__
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <ctype.h>

#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201
#endif

/**
 * Struct containing client's information
 * @param data some data
 * @param prev previous client
 * @param link some link
 * @param ip client's ip
 * @param name client's name
*/
typedef struct ClientNode 
{
    int data;

    struct ClientNode* prev;
    struct ClientNode* link;

    char ip[16];
    char name[31];
} ClientList;

/**
 * Create new node on clients list
 * @param sockfd socket stuff
 * @param ip client's IP
*/
ClientList* newNode(int sockfd, char* ip);

extern ClientList* root;

/**
 * Struct containing all arguments for `client_handler` function
 * @param now now
 * @param p_client client
*/
typedef struct ClientArg
{
    ClientList* now;
    void *p_client;
} ClientArg;

/**
 * Catch Ctrl-C and handle it
 * @param sig signal number
*/
void catch_ctrl_c_and_exit(int sig);

/**
 * Send number to all clients
 * @param fmt message to send to all clients
*/
void send_to_all_clients(const char* fmt, ...);

/**
 * Handle clients
 * @param client_arg arguments in struct because we pass this function to `pthread_create`
*/
void* client_handler(void* client_arg);
