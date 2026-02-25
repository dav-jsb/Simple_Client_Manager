#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

typedef struct{
    char* name;
    char* email;
    char* password;
} Client;

typedef struct{
    Client* data;
    int front;
    long int size;
} Queue;

#endif