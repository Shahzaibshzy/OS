// disk_scheduler.c
#include "disk_scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REQUESTS 100

void runDiskScheduler() {
    int requests[MAX_REQUESTS], n, current, i, totalSeek = 0, visited[MAX_REQUESTS] = {0};

    printf("\n=== Disk Scheduler (SSTF) ===\n");
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests (cylinder numbers):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter current head position: ");
    scanf("%d", &current);

    FILE *log = fopen("logs/disk_io.log", "a");
    fprintf(log, "\n[SSTF Scheduling Start] Current Head: %d\n", current);

    for (i = 0; i < n; i++) {
        int min = 99999, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(current - requests[j]) < min) {
                min = abs(current - requests[j]);
                index = j;
            }
        }

        if (index != -1) {
            visited[index] = 1;
            totalSeek += abs(current - requests[index]);
            fprintf(log, "Moving from %d to %d (Seek = %d)\n", current, requests[index], abs(current - requests[index]));
            current = requests[index];
        }
    }

    fprintf(log, "Total Seek Time: %d\n", totalSeek);
    fclose(log);

    printf("SSTF scheduling complete. Total seek time: %d\n", totalSeek);
}
