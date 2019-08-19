CC = gcc

CFLAGS = -Wall

LDFLAGS = 

SOURCES = vigenere_encryptor.c vigenere_encryptor_mult.c
OBJS = $(SOURCES: .c=.o)
EXEC = vigenere_mult vigenere

all: $(EXEC)

$(EXECS): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f *.o $(EXEC)

clobber:
	rm -f *~ \#*