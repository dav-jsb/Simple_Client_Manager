#ifndef QUEUE_H
#define QUEUE_H

#include <constants.h>

Queue CreateQueue();

int IsEmpty(Queue queue);

Client CreateClient(const char* name, const char* email, const char* password);

void Push(Queue* queue, Client client);

#endif