// security_module.h
#ifndef SECURITY_MODULE_H
#define SECURITY_MODULE_H

typedef enum {ADMIN, STUDENT, GUEST} Role;

typedef struct {
    char username[50];
    Role role;
} User;

extern User currentUser;

void initializeSecurityModule(); // load user roles
int authorizeFileAction(const char* action); // check permission
void runSecurityModuleManually(); // manual test/demo
void manualReLogin();

#endif
