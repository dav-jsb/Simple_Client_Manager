#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <constants.h>
#include <nested_list.h>

int InsertClient(Client* head);

Client* ReadClient_Id(long int id);

Client* ReadClient_Email(const char* email);

int RemoveClient_Id(long int id);

int RemoveClient_Email(const char* email);

int EditName_Id(long int id, const char* newname);

int EditName_Email(const char* email, const char* newname);

typedef void (*Process)(void);

void RegisterClient(void);

void DeleteClient(void);

#endif