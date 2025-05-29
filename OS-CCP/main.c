#include <stdio.h>
#include "include/memory_manager.h"
#include "include/file_system.h"
#include "include/disk_scheduler.h"
#include "include/security_module.h"



int main() {
    freopen("log.txt", "w", stdout);
    printf("OS Simulator Running...\n");

    // Memory module
    init_page_table();
    int test_pages[] = {1, 3, 4, 1, 6, 3, 7, 2, 4, 5};
    for (int i = 0; i < 10; i++) {
        access_page(test_pages[i]);
        log_memory_utilization();
    };
    print_page_table();
    printf("\nTotal Page Faults: %d\n", get_page_faults());

    // File system module
    printf("\n--- FILE SYSTEM TESTS ---\n");
    init_file_system();

    create_file("file1.txt", READ_WRITE);
    create_file("readonly.txt", READ_ONLY);

    write_file("file1.txt", "This is a writable file.");
    write_file("readonly.txt", "Attempting write to read-only file.");

    read_file("file1.txt");
    read_file("readonly.txt");

    list_files();

    delete_file("readonly.txt");
    list_files();


    printf("\n--- DISK SCHEDULER TESTS ---\n");
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests)/sizeof(requests[0]);
    int head_start = 53;

    run_fcfs(requests, n, head_start);
    run_sstf(requests, n, head_start);
    run_scan(requests, n, head_start, 1); // 1 = right



    printf("\n--- SECURITY TESTS ---\n");

    set_current_user(ROLE_ADMIN);
    log_access_attempt("file1.txt", "delete", has_permission("delete"));

    set_current_user(ROLE_STUDENT);
    log_access_attempt("file1.txt", "write", has_permission("write"));
    log_access_attempt("file1.txt", "delete", has_permission("delete"));

    set_current_user(ROLE_GUEST);
    log_access_attempt("file1.txt", "read", has_permission("read"));
    log_access_attempt("file1.txt", "write", has_permission("write"));



    return 0;
}
