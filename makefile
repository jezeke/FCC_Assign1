CC = gcc
CFLAGS = -Wall -lm -Ofast
TARGET = sdes

all: $(TARGET) permute_test

$(TARGET) : sdes.o permute.o
	$(CC) $(CFLAGS) sdes.o permute.o -o $(TARGET)

sdes.o : sdes.c sdes.h permute.h
	$(CC) $(CFLAGS) -c sdes.c

permute_test : permute.o permuteTest.c
	$(CC) $(CFLAGS) -g permuteTest.c permute.o -o permute_test

permute.o : permute.c permute.h
	$(CC) $(CFLAGS) -c permute.c

clean :
	rm $(TARGET) permute.o sdes.o permute_test
