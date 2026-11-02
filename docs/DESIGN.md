# mec_engine Core Components Design

## Table Metadata Design

- char *table_name: Name of the table.
- uint64_t column_count: Represents the number of columns in the table.
- char **datatypes: Datatypes of all the columns. Allowed types for now are `integer`, `string`, `double` and `boolean`.

## Table Design

- void *data: The data matrix flattened out.
- TableMetadata *metadata: The metadata for this table.

## Database Design

- char *database_name: Name of the database.
- Table **tables: Array of pointers to the tables.
