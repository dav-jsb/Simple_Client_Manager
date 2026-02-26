#include <nested_list.h>

void FreeHead(Client* head){
    free(head->name);
    free(head->email);
    free(head->password);
    free(head);
}

int IsEmpty(Client* head){
    return head == NULL;
}

void FreeMem(Client* head){
    if (!IsEmpty(head)){
        Client* temp = head->next;
        FreeHead(head);
        head = temp;
    }
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
        (head->name = (char*) malloc(sizeof(char) * (strlen(name) + 1))) == NULL ||
        (head->email = (char*) malloc(sizeof(char) * (strlen(email) + 1))) == NULL ||
        (head->password = (char*) malloc(sizeof(char) * (strlen(password) + 1))) == NULL
    ){
        printf("Memory allocation error!");
        FreeHead(head);
        return NULL;
    }
    
    head->next = NULL;
    head->id = id;
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

void RemoveList(Client* head, long int id){
    int boolean = 0;

    if (head == NULL){
        boolean = 1;
        printf("Empty list!");
    }
    
    if (!boolean && head->id == id){
        Client* temp = head->next;
        FreeHead(head);
        head = temp;
        boolean = 1;
    }

    Client* temp = head;

    while (temp != NULL && !boolean){
        if (temp->next->id == id){
            Client* temp2 = temp->next;
            temp->next = temp2->next;
            FreeHead(temp2);
            boolean = 1;
        }
    }

    if (!boolean){
        printf("Client is not in list!");
    }

    else{
        printf("Sucessfully removed element!");
    }
}

void PrintList(Client* head){
    if (head == NULL){
        printf("Empty list!");
    }

    else{
        Client* temp = head;
        while (temp != NULL){
            printf("%d %s %s %s\n", temp->id, temp->name, temp->email, temp->password);
            temp = temp->next;
        }
    }
}