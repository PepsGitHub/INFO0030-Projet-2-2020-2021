### 
## Makefile skeleton
## INFO0030: Projet 2
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g
LD=gcc
LDFLAGS=

# Files
EXEC=basic_cipher
MODULES=main.c pnm.c lfsr.c verify.c chiffrement.c
OBJECTS=main.o pnm.o lfsr.o verify.o chiffrement.o

## Rules

all: $(EXEC)

basic_cipher: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

lfsr.o: lfsr.c
	$(CC) -c lfsr.c -o lfsr.o $(CFLAGS)

verify.o: verify.c
	$(CC) -c verify.c -o verify.o $(CFLAGS)

chiffrement.o: chiffrement.c
	$(CC) -c chiffrement.c -o chiffrement.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

archive:
	tar -zcvf chiffrement.tar.gz *.h *.c *.o README.md Makefile doxygen

