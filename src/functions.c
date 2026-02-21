#include <functions.h>

void FreeMem(Queue* queue){
    for (int i = 0; i < queue->size; i++){
        free(queue->data[i].name);
        free(queue->data[i].email);
        free(queue->data[i].password);
    }

    free(queue->data);
}

void CreateDataSet(){
    FILE* file = NULL;

    if ((file = fopen("./build/dataset.txt", "w")) == NULL){
        printf("File create error!");
    }

    else fclose(file);
}