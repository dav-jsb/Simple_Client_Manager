#ifndef NESTED_LIST
#define NESTED_LIST

#include <constants.h>

void FreeHead(Client* head);

int IsEmpty(Client* head);

void FreeMem(Client* head);

Client* CreateNode(
    long int id,
    const char* name,
    const char* email,
    const char* password
);

Client* Push(
    Client* head,
    long int id,
    const char* name,
    const char* email,
    const char* password
);

void RemoveList(Client* head, long int id);

void PrintList(Client* head);

#endif