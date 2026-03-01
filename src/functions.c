#include <functions.h>

int InsertClient(Client* head){
    sqlite3* db = NULL;
    int rc = 0;
    sqlite3_stmt* stmt = NULL;
    
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

    char* sqlcmm2 = "INSERT INTO Clients (Id, Name, Email, Password) "\
    "SELECT ?, ?, ?, ? "\
    "WHERE NOT EXISTS (SELECT 1 FROM Clients WHERE Id = ? OR Email = ?)";

    if (sqlite3_prepare_v2(db, sqlcmm2, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    while (temp != NULL){
        sqlite3_bind_int64(stmt, 1, temp->id);
        sqlite3_bind_text(stmt, 2, temp->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, temp->email, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, temp->password, -1, SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 5, temp->id);
        sqlite3_bind_text(stmt, 6, temp->email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);

        if (rc == SQLITE_DONE){
            if (sqlite3_changes(db) > 0){
                printf("Sucessfully inserted client!\n");
            }

            else{
                printf("Client already exists!\n");
            }
        }

        else{
            printf("SQL error: %s", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1;
        }

        temp = temp->next;
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);
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

    sqlite3_bind_int64(stmt, 1, id);
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
    printf("Searching client with id: %ld...\n", id);

    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE){
        if (sqlite3_changes(db) > 0){
            printf("Sucessfully deleted client!\n");
        }

        else{
            printf("No found client with id: %ld\n", id);
        }
    }

    else{
        printf("Execution error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int RemoveClient_Email(const char* email){
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;

    if (sqlite3_open("./src/database.db", &db)){
        printf("Database connection error!\n");
        return 1;
    }

    const char* sqlcmm1 = "DELETE FROM Clients WHERE Email LIKE ?";

    if (sqlite3_prepare_v2(db, sqlcmm1, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    printf("Searching client with email: %s...\n", email);

    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE){
        if (sqlite3_changes(db) > 0){
            printf("Sucessfully deleted client!\n");
        }

        else{
            printf("No found client with email: %s\n", email);
        }
    }

    else{
        printf("Execution error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int EditName_Id(long int id, const char* newname){
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;

    if (sqlite3_open("./src/database.db", &db)){
        printf("Database conection error!\n");
        return 1;
    }

    const char* sqlcmm1 = "UPDATE Clients SET Name = ? WHERE Id = ?;";

    if (sqlite3_prepare_v2(db, sqlcmm1, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, newname, -1, SQLITE_STATIC);

    sqlite3_bind_int64(stmt, 2, id);

    printf("Searching client with id: %ld...\n", id);

    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE){
        if (sqlite3_changes(db) > 0){
            printf("Sucessfully updated client!\n");
        }

        else{
            printf("Client not found!\n");
        }
    }

    else{
        printf("Execution error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int EditName_Email(const char* email, const char* newname){
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;

    if (sqlite3_open("./src/database.db", &db)){
        printf("Database conection error!\n");
        return 1;
    }

    const char* sqlcmm1 = "UPDATE Clients SET Name = ? WHERE Email = ?;";

    if (sqlite3_prepare_v2(db, sqlcmm1, -1, &stmt, NULL)){
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, newname, -1, SQLITE_STATIC);

    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);

    printf("Searching client with email: %s...\n", email);

    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE){
        if (sqlite3_changes(db) > 0){
            printf("Sucessfully updated client!\n");
        }

        else{
            printf("Client not found!\n");
        }
    }

    else{
        printf("Execution error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void RegisterClient(void){
    long int id = -1;
    char* name = NULL;
    char* email = NULL;
    char* password = NULL;
    char confirm = 'n';
    int error = 0;
    Client* head = NULL;

    if ((name = (char*) malloc(sizeof(char) * 256)) == NULL ||
        (email = (char*) malloc(sizeof(char) * 256)) == NULL ||
        (password = (char*) malloc(sizeof(char) * 256)) == NULL)
    {
        printf("Memory allocation error!\n");
        error = 1;
        free(name);
        free(email);
        free(password);
    }

    if (!error){
        while (confirm == 'n'){
            printf("type here id: ");
            scanf(" %ld", &id);

            printf("type here name: ");
            scanf(" %[^\n]", name);

            printf("type here email: ");
            scanf(" %s", email);
            
            printf("type here password: ");
            scanf(" %s", password);

            confirm = 'x';

            while (confirm != 'y' && confirm != 'n' && confirm != 'c'){
                printf("confirm register? (y for yes / n for no / c for cancel): ");
                scanf(" %c", &confirm);
            }

            if (confirm == 'n'){
                head = Push(head, id, name, email, password);
            }

            if (confirm == 'y'){
                head = Push(head, id, name, email, password);
                InsertClient(head);
            }
        }
    }

    free(name);
    free(email);
    free(password);
}

void DeleteClient(void){
    long int id = -1;
    char* email = NULL;
    int error = 0;
    int select = 0;
    
    email = (char*) malloc(sizeof(char) * 256);

    if (email == NULL){
        printf("Memory allocation error!\n");
        error = 1;
    }

    if (!error){
        printf("press 1 to delete by id\n");
        printf("press 2 to delete by email\n");

        while((int)select < 1 || (int)select > 2){
            printf("type here: ");
            scanf(" %d", &select);
        }

        if (select == 1){
            printf("type here the id: ");
            scanf(" %ld", &id);
        }

        else{
            printf("type here the email: ");
            scanf(" %s", email);
            RemoveClient_Email(email);
        }
    }

    free(email);
}