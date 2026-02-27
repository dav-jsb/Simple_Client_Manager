#include <constants.h>
#include <functions.h>
#include <nested_list.h>

int main() {
    Client* head = NULL;
    head = ReadClient_Id(1);
    PrintList(head);
    FreeMem(head);
    return 0;
}