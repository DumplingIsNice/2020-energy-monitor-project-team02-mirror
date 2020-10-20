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
OBJs=obj/main.o obj/uart.o obj/common.o obj/adc.o obj/test.o obj/dsp.o obj/display.o obj/timer0.o obj/timer2.o

# Extra Debugging Flags
# Note that Proteus expects the .elf to have debugging symbols in the dwarf verison 2 format (hence -gdwarf-2)
CFLAGS_DEBUG=-g3 -gdwarf-2 -O0 -Wall -Wextra

# Compiler and Linker Flags
CFLAGS=-mmcu=atmega328p -O0 $(CFLAGS_DEBUG)
LDFLAGS=-mmcu=atmega328p

# Default Compiler/Linker Flags Used by Atmel Studio 7 On Windows.
#CFLAGS=-x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -c -std=gnu99 -gdwarf-2
#LDFLAGS=-Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328p


# Default target is to simply build the FirmWare ELF
all:$(BIN)

# Target for .ELF output binary
$(BIN):$(OBJs)
	@printf "\t- Linking Object Files Into Executable $@\n"
	@$(CC) -o $@ $(OBJs) $(LDFLAGS);

# One build target per object file / C source file (.c file NOT .h files)
obj/main.o:main.c uart.h common.h adc.h dsp.h timer0.h
	@printf "\t- Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/common.o:common.c common.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/uart.o:uart.c common.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/adc.o:adc.c common.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/test.o:test.c common.h uart.h adc.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/dsp.o:dsp.c common.h adc.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/display.o:display.c common.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/timer0.o:timer0.c common.h
	@printf "\t - Compiling $< into $@\n"
	@$(CC) -c $(CFLAGS) -o $@ $<

obj/timer2.o:timer2.c common.h
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
