#include <stdio.h>
#include <string.h>
#include "../include/security_module.h"

static UserRole current_user;

void set_current_user(UserRole role) {
    current_user = role;
}


// Add this below your existing code in security_module.c
typedef struct {
    char username[20];
    char password[20];
    UserRole role;
} User;

static User users[] = {
    {"admin", "admin123", ROLE_ADMIN},
    {"student", "stud123", ROLE_STUDENT},
    {"guest", "guest123", ROLE_GUEST}
};

UserRole authenticate(const char* username, const char* password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return users[i].role;
        }
    }
    return -1;
}


int has_permission(const char *operation) {
    if (current_user == ROLE_ADMIN) return 1;
    if (current_user == ROLE_STUDENT) {
        if (strcmp(operation, "delete") == 0) return 0;
        return 1;
    }
    if (current_user == ROLE_GUEST) {
        return strcmp(operation, "read") == 0;
    }
    return 0;
}

void log_access_attempt(const char *filename, const char *operation, int allowed) {
    if (allowed)
        printf("[SECURITY] %s performed '%s' on %s\n", 
               (current_user == ROLE_ADMIN ? "Admin" :
                current_user == ROLE_STUDENT ? "Student" : "Guest"),
               operation, filename);
    else
        printf("[SECURITY VIOLATION] %s attempted '%s' on %s — Access Denied!\n",
               (current_user == ROLE_ADMIN ? "Admin" :
                current_user == ROLE_STUDENT ? "Student" : "Guest"),
               operation, filename);
}
