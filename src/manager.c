#include <constants.h>
#include <functions.h>
#include <nested_list.h>

int main() {
    Client* head = NULL;
    head = Push(head, 2, "tes", "testado@hotmail.com", "test1234");
    InsertClient(head);
    FreeMem(head);
    return 0;
}