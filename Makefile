# all: main.c memory.c cpu.c debug.c
# 	gcc main.c memory.c cpu.c debug.c
# Detect the operating system
ifeq ($(OS),Windows_NT)
    # Windows-specific commands and settings
    EXECUTABLE = program.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # macOS-specific commands and settings
        EXECUTABLE = program
    else
        # Linux-specific commands and settings
        EXECUTABLE = program
    endif
endif

# Default target
all: $(EXECUTABLE)

# Source files
SRCS = main.c memory.c cpu.c debug.c

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra

# Build the executable
$(EXECUTABLE): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXECUTABLE)