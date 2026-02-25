#include <constants.h>

typedef struct{
    long int id;
    char* name;
    char* email;
    char* password;
    struct Client* next;
}Client;

void HeadFree(Client* head){
    free(head->name);
    free(head->email);
    free(head->password);
    free(head);
}

int IsEmpty(Client* head){
    return head == NULL;
}

Client* CreateNode(
    long int id,
    const char* name,
    const char* email,
    const char* password
){
    Client* head = NULL;

    if ((head = (Client*) malloc(sizeof(Client))) == NULL){
        printf("Create node error!");
        return NULL;
    }
    
    if (
        (name = (char*) malloc(sizeof(char) * (strlen(name) + 1))) == NULL ||
        (email = (char*) malloc(sizeof(char) * (strlen(email) + 1))) == NULL ||
        (password = (char*) malloc(sizeof(char) * (strlen(password) + 1))) == NULL
    ){
        printf("Memory allocation error!");
        HeadFree(head);
        return NULL;
    }
    
    head->id = id;
    head->next = NULL;
    strcpy(head->name, name);
    strcpy(head->email, email);
    strcpy(head->password, password);

    return head;
}

Client* Push(
    Client* head,
    long int id,
    const char* name,
    const char* email,
    const char* password
){
    if (head == NULL){
        head = CreateNode(id, name, email, password);
        return head;
    }

    Client* temp = head;
    
    while(temp->next != NULL){
        temp = temp->next;
    }
    
    temp->next = CreateNode(id, name, email, password);
    return head;
}