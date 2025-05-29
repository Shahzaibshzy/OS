#include <stdio.h>
#include <string.h>
#include "file_system.h"

static Directory root;

void init_file_system() {
    strcpy(root.name, "root");
    root.file_count = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        root.files[i].is_used = 0;
    }
}

int create_file(const char* name, Permission perm) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!root.files[i].is_used) {
            strcpy(root.files[i].name, name);
            root.files[i].permission = perm;
            root.files[i].content[0] = '\0';
            root.files[i].is_used = 1;
            root.file_count++;
            printf("[FILE SYSTEM] Created file: %s\n", name);
            return 1;
        }
    }
    printf("[ERROR] Max file limit reached!\n");
    return 0;
}

int write_file(const char* name, const char* content) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (root.files[i].is_used && strcmp(root.files[i].name, name) == 0) {
            if (root.files[i].permission == READ_ONLY) {
                printf("[ERROR] Cannot write to read-only file: %s\n", name);
                return 0;
            }
            strcpy(root.files[i].content, content);
            printf("[FILE SYSTEM] Wrote to file: %s\n", name);
            return 1;
        }
    }
    printf("[ERROR] File not found: %s\n", name);
    return 0;
}

int read_file(const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (root.files[i].is_used && strcmp(root.files[i].name, name) == 0) {
            printf("[FILE SYSTEM] Reading %s: %s\n", name, root.files[i].content);
            return 1;
        }
    }
    printf("[ERROR] File not found: %s\n", name);
    return 0;
}

int delete_file(const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (root.files[i].is_used && strcmp(root.files[i].name, name) == 0) {
            root.files[i].is_used = 0;
            root.file_count--;
            printf("[FILE SYSTEM] Deleted file: %s\n", name);
            return 1;
        }
    }
    printf("[ERROR] File not found: %s\n", name);
    return 0;
}

void list_files() {
    printf("\n[FILE LIST in /%s]\n", root.name);
    for (int i = 0; i < MAX_FILES; i++) {
        if (root.files[i].is_used) {
            printf(" - %s (%s)\n", root.files[i].name,
                   root.files[i].permission == READ_ONLY ? "Read-Only" : "Read-Write");
        }
    }
}
