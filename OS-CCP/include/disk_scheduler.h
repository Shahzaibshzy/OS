#ifndef DISK_SCHEDULER_H
#define DISK_SCHEDULER_H

void run_fcfs(int requests[], int n, int head_start);
void run_sstf(int requests[], int n, int head_start);
void run_scan(int requests[], int n, int head_start, int direction);

#endif
