#include "memory_manager.h"
#include <stdio.h>

static PageTableEntry page_table[PAGE_TABLE_SIZE];
static int memory_frames[FRAME_COUNT];
static int frame_pointer = 0;
static int page_faults = 0;

// Initialize page table and memory
void init_page_table()
{
    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        page_table[i].page_number = i;
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
    }

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        memory_frames[i] = -1;
    }

    page_faults = 0;
    frame_pointer = 0;

    FILE *log = fopen("logs/memory.log", "a");
    if (log)
    {
        fprintf(log, "\n[Paging with FIFO Start]\n");
        fclose(log);
    }
}

// FIFO page replacement with logging
int access_page(int page_number)
{
    if (page_number < 0 || page_number >= PAGE_TABLE_SIZE)
    {
        printf("[ERROR] Invalid page number: %d\n", page_number);
        return 0;
    }

    if (page_table[page_number].valid)
    {
        printf("[MEMORY] Page %d is already in frame %d\n", page_number, page_table[page_number].frame_number);
        return 0;
    }
    else
    {
        // Page fault
        page_faults++;
        int replaced_page = memory_frames[frame_pointer];

        if (replaced_page != -1)
        {
            page_table[replaced_page].valid = 0;
            page_table[replaced_page].frame_number = -1;
            printf("[MEMORY] Replacing page %d from frame %d\n", replaced_page, frame_pointer);
        }

        memory_frames[frame_pointer] = page_number;
        page_table[page_number].frame_number = frame_pointer;
        page_table[page_number].valid = 1;

        printf("[MEMORY] Loaded page %d into frame %d\n", page_number, frame_pointer);

        frame_pointer = (frame_pointer + 1) % FRAME_COUNT;
        return 1; // page fault occurred
    }
}

// Print formatted page table to console
void print_page_table()
{
    FILE *log = fopen("logs/memory.log", "a");

    printf("\n[PAGE TABLE]\n");
    printf("Page\tFrame\tValid\n");

    if (log)
        fprintf(log, "\n[PAGE TABLE]\nPage\tFrame\tValid\n");

    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        printf("%d\t%d\t%d\n", i, page_table[i].frame_number, page_table[i].valid);
        if (log)
            fprintf(log, "%d\t%d\t%d\n", i, page_table[i].frame_number, page_table[i].valid);
    }

    if (log)
        fclose(log);
}

// Print memory utilization
void log_memory_utilization()
{
    int used = 0;
    for (int i = 0; i < FRAME_COUNT; i++)
    {
        if (memory_frames[i] != -1)
            used++;
    }

    float utilization = ((float)used / FRAME_COUNT) * 100.0;

    printf("[MEMORY UTILIZATION] Used Frames: %d/%d (%.2f%%)\n",
           used, FRAME_COUNT, utilization);

    FILE *log = fopen("logs/memory.log", "a");
    if (log)
    {
        fprintf(log, "Used Frames: %d/%d (%.2f%%)\n",
                used, FRAME_COUNT, utilization);
        fclose(log);
    }
}

// Return fault count
int get_page_faults()
{
    return page_faults;
}
void runMemoryManager()
{
    int pageStream[100], n;

    printf("\n=== Memory Manager (Paging + FIFO) ===\n");
    printf("Enter number of page requests: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100)
    {
        printf("Invalid input. Returning to main menu.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("Enter page reference string (e.g., 2 3 4 2 1 5 ...):\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &pageStream[i]) != 1 || pageStream[i] < 0 || pageStream[i] >= PAGE_TABLE_SIZE)
        {
            printf("Invalid page number. Returning to main menu.\n");
            while (getchar() != '\n')
                ;
            return;
        }
    }

    init_page_table(); // Initialize everything

    FILE *log = fopen("logs/memory.log", "a");
    if (log)
    {
        fprintf(log, "\n[Paging with FIFO Start]\n");
        fclose(log);
    }

    for (int i = 0; i < n; i++)
    {
        int fault = access_page(pageStream[i]);
        if (fault)
        {
            FILE *log = fopen("logs/memory.log", "a");
            if (log)
            {
                fprintf(log, "Page Fault on request %d (Page %d)\n", i + 1, pageStream[i]);
                fclose(log);
            }
        }
    }

    printf("Page faults occurred: %d\n", get_page_faults());
    print_page_table();

    log = fopen("logs/memory.log", "a");
    if (log)
    {
        fprintf(log, "Total Page Faults: %d\n", get_page_faults());
        fprintf(log, "[Paging Session End]\n\n");
        fclose(log);
    }

    log_memory_utilization();

    while (getchar() != '\n')
        ; // Clear newline
    printf("\nPress Enter to return to main menu...");
    getchar();
}

// Final log entry
void log_paging_end()
{
    FILE *log = fopen("logs/memory.log", "a");
    if (log)
    {
        fprintf(log, "Total Page Faults: %d\n", page_faults);
        fprintf(log, "[Paging Session End]\n\n");
        fclose(log);
    }
}
