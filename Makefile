
# Detect the operating system
ifeq ($(OS),Windows_NT)
    # windows
    EXECUTABLE = a.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # mac
        EXECUTABLE = a
    else
        # linux
        EXECUTABLE = a.out
    endif
endif

# Build the executable
all: main.c memory.c cpu.c debug.c
	gcc -Wall -Wextra main.c memory.c cpu.c debug.c