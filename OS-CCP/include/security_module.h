#ifndef SECURITY_MODULE_H
#define SECURITY_MODULE_H

typedef enum {
    ROLE_ADMIN,
    ROLE_STUDENT,
    ROLE_GUEST
} UserRole;

void set_current_user(UserRole role);
int has_permission(const char *operation);
void log_access_attempt(const char *filename, const char *operation, int allowed);
UserRole authenticate(const char* username, const char* password);


#endif
