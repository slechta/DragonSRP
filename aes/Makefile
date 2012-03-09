#either asm or aescrypt.c can be used

CC = gcc
CFLAGS = -Wall -I. -O3

CCC = g++
CCFLAGS = -Wall -I. -O3

ASM = yasm


OBJ-AES =   aescrypt.o \
            aeskey.o \
            aes_modes.o \
            aestab.o

OBJ-APPS = rfc3686.o			

OBJ-DREL = drel/aesexception.o \
           drel/aescounter.o

#compile all
all: aes apps drel

#compile aes library object only
aes: $(OBJ-AES) aesasm

#compile the assebler part object file
aesasm:	aes_amd64.asm
	$(ASM) -f elf64 aes_amd64.asm

drel: $(OBJ-DREL)

#compile applications in C++
apps: aes $(OBJ-APPS)
	$(CCC) $(OBJ-AES) $(OBJ-APPS) -o rfc3686

#tells how to make an *.o object file from an *.c file
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

#tells how to make an *.o object file from an *.cpp file
%.o: %.cpp
	$(CCC) -c $(CFLAGS) $< -o $@

clean::
	rm -f *.o
	rm -f rfc3686
