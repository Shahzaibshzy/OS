// memory_manager.h
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#define PAGE_TABLE_SIZE 10 // Total virtual pages
#define FRAME_COUNT 4      // Number of available memory frames

typedef struct
{
    int page_number;
    int frame_number;
    int valid;
} PageTableEntry;

void init_page_table();
int access_page(int page_number);
void print_page_table();
void log_memory_utilization();
int get_page_faults();
void log_paging_end();
void runMemoryManager();

#endif
