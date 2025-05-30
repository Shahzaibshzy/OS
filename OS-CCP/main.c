#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/memory_manager.h"
#include "include/file_system.h"
#include "include/disk_scheduler.h"
#include "include/security_module.h"

int main() {
    freopen("log.txt", "w", stdout);
    printf("OS Simulator Running...\n");

    // --- Authentication ---
    char username[20], password[20];
    printf("Login Required\nUsername: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    UserRole role = authenticate(username, password);
    if (role == -1) {
        printf("[AUTH] Invalid credentials. Access Denied.\n");
        return 1;
    }

    set_current_user(role);
    printf("[AUTH] Login successful as %s\n",
        role == ROLE_ADMIN ? "Admin" :
        role == ROLE_STUDENT ? "Student" : "Guest");

    // --- File System Setup ---

    
    init_file_system();
    char filename[50], perm_input[10];
    Permission perm;

    printf("\n--- FILE CREATION ---\n");
    printf("Enter new file name: ");
    scanf("%s", filename);
    printf("Enter permission (ro/rw): ");
    scanf("%s", perm_input);
    perm = strcmp(perm_input, "ro") == 0 ? READ_ONLY : READ_WRITE;

    // File creation allowed only for Admin and Student
    if (has_permission("create")) {
        create_file(filename, perm);
        log_access_attempt(filename, "create", 1);
    } else {
        log_access_attempt(filename, "create", 0);
    }

    // --- File Operation ---
    char operation[10], content[100];
    printf("\n--- FILE OPERATION ---\n");
    printf("Operation to perform (read/write/delete): ");
    scanf("%s", operation);

    int allowed = has_permission(operation);
    log_access_attempt(filename, operation, allowed);

    if (!allowed) {
        printf("Access denied: You are not allowed to perform '%s'\n", operation);
    } else {
        if (strcmp(operation, "read") == 0) {
            read_file(filename);
        } else if (strcmp(operation, "write") == 0) {
            printf("Enter content to write: ");
            scanf(" %[^\n]", content);  // read line with spaces
            write_file(filename, content);
        } else if (strcmp(operation, "delete") == 0) {
            delete_file(filename);
        } else {
            printf("Invalid operation.\n");
        }
    }

    // --- Summary ---
    list_files();

    return 0;
}
