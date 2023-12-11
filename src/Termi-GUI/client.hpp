/**
 * @author Chenxu Wang, Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT license
 * DESCRIPTION: Client header file
 */

#pragma once

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

static int sockfd = 0;
static char nickname[LENGTH_NAME];

/**
 * Clear input buffer
*/
void clear_input_buffer(); 

/**
 * Overwrite stdout
*/
void str_overwrite_stdout();

/**
 * Trim \n
 * @param arr string
 * @param length length of the string
*/
void str_trim_lf(char* arr, int length);

/**
 * Convert string to uint16_t
 * @param str string for conversion
 * @param res result
*/
bool str_to_uint16(const char *str, uint16_t *res);

/**
 * Receive message from clients and from server
*/
void* recv_msg_handler();


/**
 * Send message to clients and to a server
*/
void* send_msg_handler();
