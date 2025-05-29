// src/memory_manager.c

#include <stdio.h>
#include "memory_manager.h"

static PageTableEntry page_table[PAGE_TABLE_SIZE];
static int memory_frames[FRAME_COUNT];
int frame_table[FRAME_COUNT];
static int frame_pointer = 0;
static int page_faults = 0;

void init_page_table() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].page_number = i;
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
    }

    for (int i = 0; i < FRAME_COUNT; i++) {
        memory_frames[i] = -1;
    }
}

void log_memory_utilization() {
    int used = 0;
    for (int i = 0; i < FRAME_COUNT; i++) {
        if (frame_table[i] != -1) used++;
    }
    float utilization = ((float)used / FRAME_COUNT) * 100.0;
    printf("[MEMORY UTILIZATION] Used Frames: %d/%d (%.2f%%)\n", used, FRAME_COUNT, utilization);
}


int access_page(int page_number) {
    if (page_number < 0 || page_number >= PAGE_TABLE_SIZE) {
        printf("[ERROR] Invalid page number: %d\n", page_number);
        return -1;
    }

    if (page_table[page_number].valid) {
        printf("[MEMORY] Page %d is already in frame %d\n", page_number, page_table[page_number].frame_number);
        return page_table[page_number].frame_number;
    } else {
        // Page fault
        page_faults++;
        int replaced_page = memory_frames[frame_pointer];

        if (replaced_page != -1) {
            page_table[replaced_page].valid = 0;
            page_table[replaced_page].frame_number = -1;
            printf("[MEMORY] Replacing page %d from frame %d\n", replaced_page, frame_pointer);
        }

        memory_frames[frame_pointer] = page_number;
        page_table[page_number].frame_number = frame_pointer;
        page_table[page_number].valid = 1;

        printf("[MEMORY] Loaded page %d into frame %d\n", page_number, frame_pointer);

        frame_pointer = (frame_pointer + 1) % FRAME_COUNT;
        return page_table[page_number].frame_number;
    }
}

void print_page_table() {
    printf("\n[PAGE TABLE]\n");
    printf("Page\tFrame\tValid\n");
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        printf("%d\t%d\t%d\n", i, page_table[i].frame_number, page_table[i].valid);
    }
}

int get_page_faults() {
    return page_faults;
}
