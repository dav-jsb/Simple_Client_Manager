#include <constants.h>
#include <functions.h>
#include <nested_list.h>

int main() {
    Client* head = NULL;
    head = ReadClient_Email("teste@gmail.com");
    PrintList(head);
    FreeMem(head);
    return 0;
}