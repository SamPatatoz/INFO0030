### 
## Makefile skeleton
## INFO0030: Projet 1
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=

# Files
EXEC=basic_cipher advanced_cipher
MODULES=advanced_cipher.c basic_cipher.c advanced_cipher_mod.c basic_cipher_mod.c LFSR.c pnm.c
OBJECTS=advanced_cipher.o basic_cipher.o basic_cipher_mod.o advanced_cipher_mod.o pnm.o LFSR.o

## Rules

all: $(EXEC)

basic_cipher: $(OBJECTS)
	$(LD) -o basic_cipher basic_cipher.o pnm.o LFSR.o basic_cipher_mod.o $(LDFLAGS)

advanced_cipher: $(OBJECTS)
	$(LD) -o advanced_cipher pnm.o LFSR.o basic_cipher_mod.o advanced_cipher.o advanced_cipher_mod.o$(LDFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

LFSR.o: LFSR.c
	$(CC) -c LFSR.c -o LFSR.o $(CFLAGS)

basic_cipher_mod.o: basic_cipher_mod.c
	$(CC) -c basic_cipher_mod.c -o basic_cipher_mod.o $(CFLAGS)

advanced_cipher.o: advanced_cipher.c
	$(CC) -c advanced_cipher.c -o advanced_cipher.o $(CFLAGS)

advanced_cipher_mod.o: advanced_cipher_mod.c
	$(CC) -c advanced_cipher_mod.c -o advanced_cipher_mod.o $(CFLAGS)

basic_cipher.o: basic_cipher.c
	$(CC) -c basic_cipher.c -o basic_cipher.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

