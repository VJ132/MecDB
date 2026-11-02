#ifndef MEC_ENGINE_H
#define MEC_ENGINE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    char *name;
    uint64_t column_count;
    char **datatypes;
} TableMetadata;

typedef struct {
    void *data;
    TableMetadata *metadata;
} Table;

typedef struct {
    char *name;
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

#endif // MEC_ENGINE_H
