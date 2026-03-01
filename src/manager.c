#include <constants.h>
#include <functions.h>
#include <nested_list.h>

int main() {
    int finalize = 0;

    Process table[] = {
        RegisterClient,
        DeleteClient
    };

    while (!finalize){
        int selector = -1;
        
        printf("Client Manager\n");
        printf("--------------\n");
        printf("press 1 to register a client\n");
        printf("press 2 to delete a client\n");
        printf("press 3 to finalize\n");
        
        while ((int)selector < 1 || (int)selector > 3){
            printf("type here: ");
            scanf(" %d", &selector);
        }

        if (selector == 3) finalize = 1;
        
        else{
            table[selector - 1]();
        }
    }
    
    return 0;
}