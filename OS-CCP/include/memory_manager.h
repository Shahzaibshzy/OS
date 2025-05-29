// include/memory_manager.h

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#define PAGE_TABLE_SIZE 8
#define FRAME_COUNT 4

typedef struct {
    int page_number;
    int frame_number;
    int valid;
} PageTableEntry;

void init_page_table();
void log_memory_utilization();
int access_page(int page_number);
void print_page_table();
int get_page_faults();

#endif
