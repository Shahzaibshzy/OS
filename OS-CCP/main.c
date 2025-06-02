// main.c
#include <stdio.h>
#include <stdlib.h>
#include "memory_manager.h"
#include "file_system.h"
#include "disk_scheduler.h"
#include "security_module.h"

// Displays the main menu
void displayMenu() {
    printf("\n===== OS Resource Manager =====\n");
    fflush(stdout);
    
    printf("1. Memory Manager\n");
    fflush(stdout);
    printf("2. File System\n");
    fflush(stdout);
    
    printf("3. Disk Scheduler\n");
    fflush(stdout);
    printf("4. Security & Access Control\n");
    fflush(stdout);
    printf("5. Manual Re-login\n");
    fflush(stdout);
    printf("6. Exit\n");
    fflush(stdout);
    printf("Select Module to Run: ");
}

int main() {
    int choice;

    // Initialize security users/roles at start
    initializeSecurityModule();  

    while (1) {
        displayMenu();
        
        // Validate integer input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            fflush(stdout);
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        getchar();  // Clear newline after number

        switch (choice) {
            case 1:
                runMemoryManager();
                break;
            case 2:
                runFileSystem();  // Enforces role-based security
                break;
            case 3:
                runDiskScheduler();  // Uses SSTF
                break;
            case 4:
                runSecurityModuleManually();  // Manual login/re-login
                break;
            case 5:
                manualReLogin();  // Allows re-login to change user roles
                break;
            case 6:
                printf("Exiting OS Resource Manager.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
