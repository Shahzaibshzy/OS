#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "file_system.h"

// Common constants
#define MAX_NAME_LENGTH 256
#define MAX_PATH_LENGTH 512
#define MAX_PROCESSES 100
#define MAX_FILES 1000
#define MAX_USERS 50
#define LOG_FILE "system.log"
#define PAGE_TABLE_SIZE 256
#define FRAME_COUNT 128

// User roles
typedef enum
{
    GUEST = 0,
    STUDENT = 1,
    ADMIN = 2
} UserRole;
typedef struct
{
    int frame_number;
    bool valid;
    bool dirty;
} PageTableEntry;
typedef struct
{
    char name[50];
    FilePermission permission;
    char content[256];
    bool is_used;
} File;

typedef struct {
    char name[50];
    File files[100];
    int file_count;
} Directory;

typedef enum
{
    ROLE_ADMIN,
    ROLE_STUDENT,
    ROLE_GUEST
} UserRole;
// User structure
typedef struct
{
    int user_id;
    char username[MAX_NAME_LENGTH];
    UserRole role;
    bool active;
} User;

// Logging functions
void log_message(const char *module, const char *message);
void log_security_violation(const char *username, const char *action, const char *resource);

#endif