#include <constants.h>
#include <functions.h>
#include <nested_list.h>

int main() {
    Client* head = NULL;
    head = Push(head, 1, "cleber", "teste@gmail.com", "123");
    head = Push(head, 2, "cle", "testado@gmail.com", "123456");
    head = Push(head, 1, "eber", "ste@gmail.com", "123789");
    PrintList(head);
    FreeMem(head);
    return 0;
}