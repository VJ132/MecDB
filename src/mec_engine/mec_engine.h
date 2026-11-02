#ifndef MEC_ENGINE_H
#define MEC_ENGINE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    char *name;
    void *data;
    uint64_t column_count;
    char **datatypes;
} Table;

typedef struct {
    char *name;
    size_t table_count;
    Table **tables;
} Database;

typedef struct {
    size_t count;
    Database **databases;
} ActiveDatabases;

extern ActiveDatabases active_databases;

bool create_database(const char *name);
bool delete_database(const char *name);
bool rename_database(const char *current_name, const char *new_name);

bool create_table(const char *database_name, const char *table_name);

#endif // MEC_ENGINE_H
