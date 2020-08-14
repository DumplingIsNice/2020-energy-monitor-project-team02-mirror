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
OBJs=obj/main.o

# Extra Debugging Flags that are used for debugging builds 
CFLAGS_DEBUG=-g -O0 -Wall -Wextra

# Compiler and Linker Flags
CFLAGS=-std=c89 -pedantic-errors -mmcu=atmega328p $(CFLAGS_DEBUG)
LDFLAGS=#-mmcu=atmega328p


# Default is debug build
all:$(BIN)

# Target for .ELF output binary 
$(BIN):$(OBJs)
	@printf "\t- Linking Object FIles Into Executable $@\n"
	@$(CC) -o $@ $(OBJs) $(LDFLAGS);

# One build target per object file / C source file (.c file NOT .h files)
obj/main.o:main.c
	@printf "\t- Compiling $< into $@\n"
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
