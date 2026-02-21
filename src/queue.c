#include <queue.h>

Queue CreateQueue(){
    Queue queue;
    queue.data = NULL;
    queue.front = -1;
    queue.size = 0;
    return queue;
}

int IsEmpty(Queue queue){
    return queue.front == -1;
}

Client CreateClient(const char* name, const char* email, const char* password){
    Client client;

    if (
        ((client.name = (char*) malloc(sizeof(char) * (strlen(name) + 1))) == NULL) ||
        ((client.email = (char*) malloc(sizeof(char) * (strlen(email) + 1))) == NULL) ||
        ((client.password = (char*) malloc(sizeof(char) * (strlen(password) + 1))) == NULL)
    ){
        printf("Memory allocation error!");
        exit(1);
    }

    strcpy(client.name, name);
    strcpy(client.email, email);
    strcpy(client.password, password);

    return client;
}

void Push(Queue* queue, Client client){
    if (IsEmpty(*queue)){
        if ((queue->data = (Client*) malloc(sizeof(Client) * 5)) == NULL){
            printf("Memory allocation error!");
            exit(1);
        }

        else queue->front++;
    }

    else{
        if (!(queue->size % 5)){
            Client* temp = NULL;
            if ((temp = (Client*) realloc(queue->data, sizeof(Client) * (queue->size + 5))) == NULL){
                printf("Memory allocation error!");
                exit(1);
            }

            else queue->data = temp;
        }
    }

    queue->size++;
    queue->data[queue->size - 1] = client;
}