#include "common.h"

void log_message(const char* module, const char* message) {
    FILE* log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        printf("ERROR: Could not open log file\n");
        return;
    }
    
    time_t now = time(NULL);
    char* time_str = ctime(&now);
    // Remove newline from time string
    time_str[strlen(time_str) - 1] = '\0';
    
    fprintf(log_file, "[%s] [%s] %s\n", time_str, module, message);
    fflush(log_file);
    fclose(log_file);
    
    // Also print to console for immediate feedback
    printf("[%s] [%s] %s\n", time_str, module, message);
}

void log_security_violation(const char* username, const char* action, const char* resource) {
    FILE* log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        printf("ERROR: Could not open log file\n");
        return;
    }
    
    time_t now = time(NULL);
    char* time_str = ctime(&now);
    // Remove newline from time string
    time_str[strlen(time_str) - 1] = '\0';
    
    fprintf(log_file, "[%s] [SECURITY_VIOLATION] User: %s, Action: %s, Resource: %s\n", 
            time_str, username, action, resource);
    fflush(log_file);
    fclose(log_file);
    
    // Also print to console with warning
    printf("*** SECURITY VIOLATION *** [%s] User: %s, Action: %s, Resource: %s\n", 
           time_str, username, action, resource);
}