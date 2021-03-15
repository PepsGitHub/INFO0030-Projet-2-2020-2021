### 
## Makefile skeleton
## INFO0030: Projet 2
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=

# Files
EXEC=basic_cipher advanced_cipher lfsr_tests archive doc

## Rules

all: $(EXEC)

pnm_tests: pnm_tests.o pnm.o seatest.o verify.o
	$(LD) -o pnm_tests pnm_tests.o pnm.o seatest.o verify.o

lfsr_tests: lfsr_tests.o lfsr.o seatest.o pnm.o verify.o
	$(LD) -o lfsr_tests lfsr_tests.o lfsr.o seatest.o pnm.o verify.o

basic_cipher: main.o pnm.o lfsr.o verify.o cipher.o
	$(LD) -o basic_cipher main.o pnm.o lfsr.o verify.o cipher.o

advanced_cipher: main.o pnm.o lfsr.o verify.o cipher.o
	$(LD) -o advanced_cipher main.o pnm.o lfsr.o verify.o cipher.o

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

pnm_tests.o: pnm_tests.c
	$(CC) -c pnm_tests.c -o pnm_tests.o $(CFLAGS)

lfsr.o: lfsr.c
	$(CC) -c lfsr.c -o lfsr.o $(CFLAGS)

lfsr_tests.o: lfsr_tests.c
	$(CC) -c lfsr_tests.c -o lfsr_tests.o $(CFLAGS)

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

verify.o: verify.c
	$(CC) -c verify.c -o verify.o $(CFLAGS)

cipher.o: cipher.c
	$(CC) -c cipher.c -o cipher.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

archive:
	tar -zcvf chiffrement.tar.gz *.h *.c *.o README.md Makefile doc

.PHONY: doc
doc:
	@doxygen Doxyfile


