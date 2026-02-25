#include <functions.h>

void CreateDataSet(){
    FILE* file = NULL;

    if ((file = fopen("./build/dataset.txt", "w")) == NULL){
        printf("File create error!");
    }

    else fclose(file);
}