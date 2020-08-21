# UNIX Makefile for compiling the firmware.
# Assumes the following are installed and in the $PATH :
# 	avr-gcc (cross-compiler) is installed along with avr-[GNU Binutils]
# 		(i.e. avr-as avr-ld etc.)
# If these assumptions are wrong, please edit the below variables
CC=avr-gcc
AS=avr-as
LD=avr-ld

# Output Binary Name (FirmWare.ELF)
BIN=FW.ELF

# List of Object Files To Link (One per .c Source File)
OBJs=obj/main.o obj/uart.o obj/common.o

# Extra Debugging Flags
CFLAGS_DEBUG=-g -O0 -Wall -Wextra

# Compiler and Linker Flags
CFLAGS=-mmcu=atmega328p $(CFLAGS_DEBUG)
LDFLAGS=-lm


# Default target is to simply build the FirmWare ELF
all:$(BIN)

# Target for .ELF output binary
$(BIN):$(OBJs)
	@printf "\t- Linking Object Files Into Executable $@\n"
	@$(CC) -o $@ $(OBJs) $(LDFLAGS);

# One build target per object file / C source file (.c file NOT .h files)
obj/main.o:main.c uart.h common.h
	@printf "\t- Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/common.o:common.c
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/uart.o:uart.c
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

# Clean Target
.PHONY: clean
clean:
	@printf "\t* Removing File $(BIN)\n"
	@$(shell rm $(BIN) 2>/dev/null)
	@printf "\t* Removing Object Files\n"
	@$(shell rm $(OBJs) 2>/dev/null)

.PHONY: rebuild
rebuild:clean all
