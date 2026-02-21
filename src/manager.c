#include <constants.h>
#include <functions.h>
#include <queue.h>

int main() {
    Client client = CreateClient("roberto", "josias@gmail.com", "1234");
    Queue queue = CreateQueue();

    Push(&queue, client);

    printf("%s", queue.data[0].name);

    FreeMem(&queue);

    return 0;
}