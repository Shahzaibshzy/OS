#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define MAX_FILES 100
#define MAX_NAME_LENGTH 32
#define MAX_CONTENT_LENGTH 256

typedef enum {
    READ_ONLY,
    READ_WRITE
} Permission;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    Permission permission;
    int is_used;
} File;

typedef struct {
    char name[MAX_NAME_LENGTH];
    File files[MAX_FILES];
    int file_count;
} Directory;

void init_file_system();
int create_file(const char* name, Permission perm);
int write_file(const char* name, const char* content);
int read_file(const char* name);
int delete_file(const char* name);
void list_files();

#endif
