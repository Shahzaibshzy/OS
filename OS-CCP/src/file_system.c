// file_system.c
#include "file_system.h"
#include "security_module.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void logFileAction(const char *action, const char *filename) {
    FILE *log = fopen("logs/filesystem.log", "a");
    fprintf(log, "[%s] User: %s, File: %s\n", action, currentUser.username, filename);
    fclose(log);
}

void createFile() {
    if (!authorizeFileAction("write")) return;

    char filename[100];
    printf("Enter file name to create: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "w");
    if (f != NULL) {
        fprintf(f, "Owner: %s\n", currentUser.username);
        fclose(f);
        printf("File '%s' created.\n", filename);
        logFileAction("CREATE", filename);
    } else {
        printf("Error creating file.\n");
    }
}

void readFile() {
    if (!authorizeFileAction("read")) return;

    char filename[100];
    printf("Enter file name to read: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        char ch;
        while ((ch = fgetc(f)) != EOF)
            putchar(ch);
        fclose(f);
        logFileAction("READ", filename);
    } else {
        printf("File not found.\n");
    }
}

void writeFile() {
    if (!authorizeFileAction("write")) return;

    char filename[100], content[1024];
    printf("Enter file name to write/append: ");
    scanf("%s", filename);
    getchar();  // clear newline
    printf("Enter content to append:\n");
    fgets(content, sizeof(content), stdin);

    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s\n", content);
        fclose(f);
        printf("Content written to '%s'.\n", filename);
        logFileAction("WRITE", filename);
    } else {
        printf("File not found or cannot write.\n");
    }
}

void deleteFile() {
    if (!authorizeFileAction("delete")) return;

    char filename[100];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File '%s' deleted.\n", filename);
        logFileAction("DELETE", filename);
    } else {
        printf("Could not delete file '%s'.\n", filename);
    }
}

void runFileSystem() {
    int choice;
    while (1) {
        printf("\n=== File System ===\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Write/Append to File\n");
        printf("4. Delete File\n");
        printf("5. Back to Main Menu\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();  // flush newline

        switch (choice) {
            case 1: createFile(); break;
            case 2: readFile(); break;
            case 3: writeFile(); break;
            case 4: deleteFile(); break;
            case 5: return;
            default: printf("Invalid option.\n");
        }
    }
}
