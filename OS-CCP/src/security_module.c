// security_module.c
#include "security_module.h"
#include <stdio.h>
#include <string.h>

User currentUser;

void initializeSecurityModule() {
    printf("Enter username: ");
    scanf("%s", currentUser.username);
    getchar();
    char roleInput[20];
    printf("Enter role (admin/student/guest): ");
    scanf("%s", roleInput);
    getchar();

    if (strcmp(roleInput, "admin") == 0)
        currentUser.role = ADMIN;
    else if (strcmp(roleInput, "student") == 0)
        currentUser.role = STUDENT;
    else
        currentUser.role = GUEST;

    printf("User '%s' logged in as %s.\n", currentUser.username, roleInput);
}

int authorizeFileAction(const char* action) {
    if (currentUser.role == ADMIN) return 1;
    if ((strcmp(action, "read") == 0) && (currentUser.role == STUDENT || currentUser.role == GUEST))
        return 1;

    // Log violation
    FILE *log = fopen("logs/security.log", "a");
    fprintf(log, "SECURITY VIOLATION: User %s tried to '%s' without permission.\n", currentUser.username, action);
    fclose(log);
    
    printf("Access denied for action '%s'.\n", action);
    return 0;
}

void runSecurityModuleManually() {
    char action[20];
    printf("Test security module\nEnter action to authorize (read/write/delete/update): ");
    scanf("%s", action);
    if (authorizeFileAction(action))
        printf("Action '%s' authorized.\n", action);
}

void manualReLogin() {
    printf("\n-- Manual Re-login --\n");
    initializeSecurityModule();
}