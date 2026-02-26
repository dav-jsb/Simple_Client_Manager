#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

typedef struct Client{
    long int id;
    char* name;
    char* email;
    char* password;
    struct Client* next;
}Client;

#endif