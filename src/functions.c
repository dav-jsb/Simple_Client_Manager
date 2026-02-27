#include <functions.h>

int InsertClient(Client* head){
    sqlite3* db = NULL;
    int rc = 0;
    
    if ((rc = sqlite3_open("./src/database.db", &db))){
        printf("Database connection error!\n");
        return 1;
    }

    char* sqlcmm1 = "CREATE TABLE IF NOT EXISTS Clients ("\
    "Id INTEGER, "\
    "Name TEXT, " \
    "Email TEXT, " \
    "Password TEXT);";

    char* errmsg = NULL;

    if ((rc = sqlite3_exec(db, sqlcmm1, NULL, 0, &errmsg))){
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
        "WHERE NOT EXISTS (SELECT 1 FROM Clients WHERE Id = %ld OR Email = '%s')";

        sprintf(sqlcmm2, tempcmm, temp->id, temp->name, temp->email, temp->password, temp->id, temp->email);

        if ((rc = sqlite3_exec(db, sqlcmm2, 0, 0, &errmsg)) == 1){
            printf("SQL error: %s\n", errmsg);
            sqlite3_free(errmsg);
            sqlite3_close(db);
            free(sqlcmm2);
            return 1;
        }

        free(sqlcmm2);
        temp = temp->next;
    }

    sqlite3_close(db);
    FreeMem(head);
    return 0;
}

Client* ReadClient_Id(long int id){
    Client* head = NULL;
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    int rc = 0;

    if (sqlite3_open("./src/database.db", &db)){
        printf("Database conection error!\n");
        return NULL;
    }

    char* sqlcmm = "SELECT Id, Name, Email, Password FROM Clients "\
    "WHERE Id = ?;";

    if (sqlite3_prepare_v2(db, sqlcmm, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, id);
    printf("Searching client with Id: %ld...\n", id);
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW){
        int returnedId = sqlite3_column_int(stmt, 0);
        const char* returnedName = (const char*) sqlite3_column_text(stmt, 1);
        const char* returnedEmail = (const char*) sqlite3_column_text(stmt, 2);
        const char* returnedPassword = (const char*) sqlite3_column_text(stmt, 3);

        head = Push(head, returnedId, returnedName, returnedEmail, returnedPassword);
    }

    else if (rc == SQLITE_DONE){
        printf("No user found with id: %ld\n", id);
    }

    else{
        printf("Execution error: %s", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return head;
}

Client* ReadClient_Email(const char* email){
    Client* head = NULL;
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    int rc = 0;

    if (sqlite3_open("./src/database.db", &db)){
        printf("Database conection error!\n");
        return NULL;
    }

    char* sqlcmm = "SELECT Id, Name, Email, Password FROM Clients "\
    "WHERE Email LIKE ?;";

    if (sqlite3_prepare_v2(db, sqlcmm, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    printf("Searching client with Email: %s...\n", email);
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW){
        int returnedId = sqlite3_column_int(stmt, 0);
        const char* returnedName = (const char*) sqlite3_column_text(stmt, 1);
        const char* returnedEmail = (const char*) sqlite3_column_text(stmt, 2);
        const char* returnedPassword = (const char*) sqlite3_column_text(stmt, 3);

        head = Push(head, returnedId, returnedName, returnedEmail, returnedPassword);
    }

    else if (rc == SQLITE_DONE){
        printf("No user found with email: %s\n", email);
    }

    else{
        printf("Execution error: %s", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return head;
}

int RemoveClient_Id(long int id){
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;

    if (sqlite3_open("./src/database.db", &db)){
        printf("Database connection error!\n");
        return 1;
    }

    const char* sqlcmm1 = "DELETE FROM Clients WHERE Id = ?";

    if (sqlite3_prepare_v2(db, sqlcmm1, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int64(stmt, 1, id);
    printf("Searching client with id: %d...\n", id);

    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE){
        if (sqlite3_changes(db) > 0){
            printf("Sucessfully deleted client!\n");
        }

        else{
            printf("No found client with id: %ld", id);
        }
    }

    else{
        printf("Execution error: %s", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}