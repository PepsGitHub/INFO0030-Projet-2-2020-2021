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
EXEC=output
MODULES=lfsr-test.c lfsr.c seatest.c
OBJECTS=lfsr-test.o lfsr.o seatest.o

## Rules

all: $(EXEC)

output: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

lfsr-test.o: lfsr-test.c
	$(CC) -c lfsr-test.c -o lfsr-test.o $(CFLAGS)

lfsr.o: lfsr.c
	$(CC) -c lfsr.c -o lfsr.o $(CFLAGS)

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

archive:
	tar -zcvf chiffrement.tar.gz *.h *.c *.o README.md Makefile doxygen

