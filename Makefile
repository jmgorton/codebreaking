CC = gcc
CFLAGS = -Wall
LDFLAGS = 

BIN = vigenere vigenere_mult frequency_analyzer
OBJS = vigenere.o vigenere_mult.o frequency_analyzer.o

#all: vigenere vigenere_mult
all: $(BIN)

vigenere: vigenere_encryptor.c
	$(CC) $(CFLAGS) vigenere_encryptor.c -o vigenere

vigenere_mult: vigenere_encryptor_mult.c
	$(CC) $(CFLAGS) vigenere_encryptor_mult.c -o vigenere_mult

frequency_analyzer: frequency_analyzer.c
	$(CC) $(CFLAGS) frequency_analyzer.c -o frequency_analyzer

.PHONY : clean clobber
clean:
	rm -f *.o $(BIN)

clobber:
	rm -f *~ \#*

########################################################

# CC = gcc

# CFLAGS = -Wall

# LDFLAGS = 

# SOURCES = vigenere_encryptor.c vigenere_encryptor_mult.c
# OBJS = $(SOURCES: .c=.o)
# EXEC = vigenere_mult vigenere

# all: $(EXEC)

# $(EXEC): $(OBJS)
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# clean:
# 	rm -f *.o $(EXEC)

# clobber:
# 	rm -f *~ \#*

#########################################################

# CC=g++
# CFLAGS=-c -Wall
# LDFLAGS=
# SOURCES=main.cpp hello.cpp factorial.cpp
# OBJECTS=$(SOURCES:.cpp=.o)
# EXECUTABLE=hello

# all: $(SOURCES) $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS) 
#     $(CC) $(LDFLAGS) $(OBJECTS) -o $@

# .cpp.o:
#     $(CC) $(CFLAGS) $< -o $@
