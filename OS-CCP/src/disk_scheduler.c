#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/disk_scheduler.h"

void run_fcfs(int requests[], int n, int head_start) {
    int total_movement = 0, current = head_start;
    printf("[DISK FCFS] Head movement: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", requests[i]);
        total_movement += abs(requests[i] - current);
        current = requests[i];
    }
    printf("END\nTotal Head Movement: %d\n\n", total_movement);
}

void run_sstf(int requests[], int n, int head_start) {
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    int total_movement = 0, current = head_start;

    printf("[DISK SSTF] Head movement: ");
    for (int count = 0; count < n; count++) {
        int min = INT_MAX, index = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs(current - requests[i]) < min) {
                min = abs(current - requests[i]);
                index = i;
            }
        }
        visited[index] = 1;
        printf("%d -> ", requests[index]);
        total_movement += abs(current - requests[index]);
        current = requests[index];
    }
    printf("END\nTotal Head Movement: %d\n\n", total_movement);
}

void run_scan(int requests[], int n, int head, int direction) {
    int total_movement = 0;
    int temp[n + 1];
    int i, j = 0;

    // Copy requests and add head
    for (i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    n++;

    // Sort requests
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }

    int pos;
    for (i = 0; i < n; i++) {
        if (temp[i] == head) {
            pos = i;
            break;
        }
    }

    printf("[DISK SCAN] Head movement: ");
    if (direction == 1) { // right
        for (i = pos; i < n; i++) {
            printf("%d -> ", temp[i]);
            if (i != pos)
                total_movement += abs(temp[i] - temp[i - 1]);
        }
        for (i = pos - 1; i >= 0; i--) {
            printf("%d -> ", temp[i]);
            total_movement += abs(temp[i + 1] - temp[i]);
        }
    } else { // left
        for (i = pos; i >= 0; i--) {
            printf("%d -> ", temp[i]);
            if (i != pos)
                total_movement += abs(temp[i + 1] - temp[i]);
        }
        for (i = pos + 1; i < n; i++) {
            printf("%d -> ", temp[i]);
            total_movement += abs(temp[i] - temp[i - 1]);
        }
    }

    printf("END\nTotal Head Movement: %d\n\n", total_movement);
}
