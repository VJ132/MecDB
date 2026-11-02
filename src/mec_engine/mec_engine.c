#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mec_engine.h"

ActiveDatabases active_databases = {
    .count = 0,
    .databases = NULL
};

bool create_database(const char *name) {
    if (name == NULL)
        return false;

    for (size_t i = 0; i < active_databases.count; ++i) {
        if (strcmp(active_databases.databases[i]->name, name) == 0)
            return false;
    }

    Database *new_db = malloc(sizeof *new_db);
    if (new_db == NULL)
        return false;

    new_db->name = malloc(strlen(name) + 1);
    if (new_db->name == NULL) {
        free(new_db);
        return false;
    }

    memcpy(new_db->name, name, strlen(name) + 1);
    new_db->tables = NULL;

    Database **reallocated_databases = realloc(
        active_databases.databases,
        (active_databases.count + 1) * sizeof(*active_databases.databases)
    );
    if (reallocated_databases == NULL) {
        free(new_db->tables);
        free(new_db->name);
        free(new_db);
        return false;
    }

    reallocated_databases[active_databases.count] = new_db;
    active_databases.databases = reallocated_databases;
    active_databases.count++;

    return true;
}

bool delete_database(const char *name) {
    if (name == NULL)
        return false;

    size_t i = 0;
    for (; i < active_databases.count; ++i) {
        if (strcmp(active_databases.databases[i]->name, name) == 0)
            break;
    }

    if (i == active_databases.count)
        return false;

    // TODO: impliment function to free all tables.
    // free_tables(active_databases.databases[i]->tables);
    free(active_databases.databases[i]->name);
    free(active_databases.databases[i]);

    memmove(&active_databases.databases[i], &active_databases.databases[i + 1], (active_databases.count - 1 - i) * sizeof(*active_databases.databases));

    active_databases.count--;

    if (active_databases.count == 0) {
        free(active_databases.databases);
        active_databases.databases = NULL;
        return true;
    }

    active_databases.databases[active_databases.count] = NULL;

    Database **reallocated_databases = realloc(
        active_databases.databases,
        active_databases.count * sizeof(*active_databases.databases)
    );

    if (reallocated_databases != NULL)
        active_databases.databases = reallocated_databases;

    return true;
}

bool rename_database(const char *current_name, const char *new_name) {
    if (current_name == NULL || new_name == NULL)
        return false;

    size_t found_at = active_databases.count;

    for (size_t i = 0; i < active_databases.count; ++i) {
        if (strcmp(active_databases.databases[i]->name, current_name) == 0) {
            found_at = i;
            break;
        }
    }

    if (found_at == active_databases.count)
        return false;

    if (strcmp(active_databases.databases[found_at]->name, new_name) == 0)
        return true;

    for (size_t i = 0; i < active_databases.count; ++i) {
        if (strcmp(active_databases.databases[i]->name, new_name) == 0)
            return false;
    }

    char *temp = malloc(strlen(new_name) + 1);
    if (temp == NULL)
        return false;

    memcpy(temp, new_name, strlen(new_name) + 1);

    free(active_databases.databases[found_at]->name);
    active_databases.databases[found_at]->name = temp;

    return true;
}

int main(void) {
    bool result = create_database("TestDB");
    printf("create_database > %d, active_databases_count > %zu\n", result, active_databases.count);

    result = create_database("TestDB");
    printf("create_database > %d, active_databases_count > %zu\n", result, active_databases.count);

    result = create_database("testdb");
    printf("create_database > %d, active_databases_count > %zu\n", result, active_databases.count);

    result = delete_database("testdb");
    printf("delete_database > %d, active_databases_count > %zu\n", result, active_databases.count);

    result = delete_database("testdb");
    printf("delete_database > %d, active_databases_count > %zu\n", result, active_databases.count);

    result = rename_database("TestDB", "hello");
    printf("rename_database > %d, active_databases_count > %zu\n", result, active_databases.count);

    result = rename_database("TestDB", "hello");
    printf("rename_database > %d, active_databases_count > %zu\n", result, active_databases.count);
}
