#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file_system.h"

#define STORAGE_DIR "storage"

void init_file_system() {
    // Create storage folder if it doesn't exist
    mkdir(STORAGE_DIR);

    printf("[FILE SYSTEM] Initialized storage at ./%s/\n", STORAGE_DIR);
}

int create_file(const char* name, Permission perm) {
    char path[100];
    snprintf(path, sizeof(path), "%s/%s", STORAGE_DIR, name);

    FILE* f = fopen(path, "w");
    if (!f) {
        printf("[ERROR] Could not create file: %s\n", path);
        return 0;
    }

    fprintf(f, "[PERMISSION] %s\n", perm == READ_ONLY ? "READ_ONLY" : "READ_WRITE");
    fclose(f);

    printf("[FILE SYSTEM] Created file: %s with %s permission\n",
           name, perm == READ_ONLY ? "Read-Only" : "Read-Write");

    return 1;
}

int write_file(const char* name, const char* content) {
    char path[100];
    snprintf(path, sizeof(path), "%s/%s", STORAGE_DIR, name);

    FILE* f = fopen(path, "r+");
    if (!f) {
        printf("[ERROR] File not found: %s\n", name);
        return 0;
    }

    char perm_line[50];
    fgets(perm_line, sizeof(perm_line), f);

    if (strstr(perm_line, "READ_ONLY")) {
        printf("[ERROR] Cannot write to read-only file: %s\n", name);
        fclose(f);
        return 0;
    }

    fseek(f, 0, SEEK_END); // move to end of file
    fprintf(f, "%s\n", content);
    fclose(f);

    printf("[FILE SYSTEM] Wrote to file: %s\n", name);
    return 1;
}

int read_file(const char* name) {
    char path[100];
    snprintf(path, sizeof(path), "%s/%s", STORAGE_DIR, name);

    FILE* f = fopen(path, "r");
    if (!f) {
        printf("[ERROR] File not found: %s\n", name);
        return 0;
    }

    char line[200];
    printf("[FILE SYSTEM] Reading %s:\n", name);
    while (fgets(line, sizeof(line), f)) {
        printf("  %s", line);
    }

    fclose(f);
    return 1;
}

int delete_file(const char* name) {
    char path[100];
    snprintf(path, sizeof(path), "%s/%s", STORAGE_DIR, name);

    if (access(path, F_OK) != 0) {
        printf("[ERROR] File not found: %s\n", name);
        return 0;
    }

    if (remove(path) == 0) {
        printf("[FILE SYSTEM] Deleted file: %s\n", name);
        return 1;
    } else {
        printf("[ERROR] Could not delete file: %s\n", name);
        return 0;
    }
}

void list_files() {
    printf("\n[FILE LIST in ./%s/]\n", STORAGE_DIR);
    system("ls -l storage | tail -n +2"); // simple list
}
