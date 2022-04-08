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
EXEC=codebarre
EXEC-TEST=codebarre_test
DEBUG=debug
MODULES=main.c pnm.c codebarre.c codebarreCorrection.c
OBJECTS=main.o pnm.o codebarre.o codebarreCorrection.o
MODULES-TEST=pnm.c seatest.c codebarre.c codebarreCorrection.c codebarre-test.c
OBJECTS-TEST=pnm.o seatest.o codebarre.o codebarreCorrection.o codebarre-test.o
DOXYGEN=doxygen

## Rules

all: $(EXEC)


#----------
# EXE
#----------
codebarre: $(OBJECTS)
	$(LD) -lm -o $(EXEC) $(OBJECTS) $(LDFLAGS) -L -libpnm

codebarre-test.o: codebarre-test.c
	$(CC) -c codebarre-test.c -o codebarre-test.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

codebarre.o: codebarre.c
	$(CC) -c codebarre.c -o codebarre.o $(CFLAGS)

codebarreCorrection.o: codebarreCorrection.c
	$(CC) -c codebarreCorrection.c -o codebarreCorrection.o $(CFLAGS)

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)


#----------
# Archive
#----------
archive:
	tar -zcvf codebarre.tar.gz *.h *.c Makefile Doxyfile

#----------
# Lib
#----------
libpnm.a: pnm.o
	ar rcs libpnm.a pnm.o
	ranlib libpnm.a

lib: libpnm.a

#----------
# Debug
#----------
debug:
	$(CC) -g $(MODULES) -o $(DEBUG)

#----------
# Test
#----------
test: $(OBJECTS-TEST)
	$(LD) -o $(EXEC-TEST) $(OBJECTS-TEST) $(LDFLAGS)

#----------
# Documentation
#----------
doc:
	mkdir doc
	$(DOXYGEN) Doxyfile

#----------
# Clean
#----------
clean:
	rm -f *.o $(EXEC) $(EXEC-TEST) $(DEBUG) *.a *.bak codebarre.tar.gz*~
	rm -r doc


