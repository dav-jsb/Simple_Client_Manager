#include <constants.h>
#include <functions.h>
#include <queue.h>

int main() {
    Client client = CreateClient("roberto", "josias@gmail.com", "1234");
    Queue queue = CreateQueue();
    sqlite3* db;

    Push(&queue, client);

    printf("%s", queue.data[0].name);

    return 0;
}