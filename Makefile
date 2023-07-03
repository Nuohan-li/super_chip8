# all: main.c memory.c cpu.c debug.c
# 	gcc main.c memory.c cpu.c debug.c

# Detect the operating system
ifeq ($(OS),Windows_NT)
    # windows
    EXECUTABLE = a.exe
    INCLUDE = -I win64_sdl/include -L win64_sdl/lib
    MINGWSDL = -lmingw32 -lSDL2main -lSDL2
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

# Default target
all: $(EXECUTABLE)

# Source files
SRCS = main.c memory.c cpu.c debug.c

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra

# Build the executable
$(EXECUTABLE): $(SRCS)
	gcc -Wall -Wextra $(INCLUDE) $(SRCS) -o $(EXECUTABLE) $(MINGWSDL)