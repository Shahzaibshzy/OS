# Makefile for OS Simulator

CC = gcc
CFLAGS = -Wall -Iinclude
SRC = main.c src/memory_manager.c src/file_system.c src/disk_scheduler.c src/security_module.c

TARGET = simulator

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f simulator.exe
