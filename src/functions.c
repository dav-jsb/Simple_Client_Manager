#include <functions.h>

int InsertClient(Client* head){
    sqlite3* db = NULL;
    int rc = 0;
    
    if (rc = sqlite3_open("./src/database.db", &db)){
        printf("Database connection error!\n");
        return 1;
    }

    char* sqlcmm1 = "CREATE TABLE IF NOT EXISTS Clients ("\
    "Id INTEGER, "\
    "Name TEXT, " \
    "Email TEXT, " \
    "Password TEXT);";

    char* errmsg = NULL;

    if (rc = sqlite3_exec(db, sqlcmm1, NULL, 0, &errmsg)){
        printf("SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }

    Client* temp = head;

    while (temp != NULL){
        char* sqlcmm2 = (char*) malloc(sizeof(char) * 512);

        if (sqlcmm2 == NULL){
            printf("Memory allocation error!\n");
            sqlite3_close(db);
            return 1;
        }

        char* tempcmm = "INSERT INTO Clients (Id, Name, Email, Password) "\
        "SELECT %ld, '%s', '%s', '%s' "\
        "WHERE NOT EXISTS (SELECT 1 FROM Clients WHERE Id = %ld)";

        sprintf(sqlcmm2, tempcmm, temp->id, temp->name, temp->email, temp->password, temp->id);

        if ((rc = sqlite3_exec(db, sqlcmm2, 0, 0, &errmsg)) == 1){
            printf("SQL error: %s\n", errmsg);
            sqlite3_free(errmsg);
            sqlite3_close(db);
            free(sqlcmm2);
            return 1;
        }

        printf("Sucessfully inserted client!\n");
        free(sqlcmm2);
        temp = temp->next;
    }

    sqlite3_close(db);
    return 0;
}