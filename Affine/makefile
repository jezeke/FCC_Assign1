CC = gcc
CFLAGS = -Wall
TARGET = affine

all: $(TARGET)

$(TARGET) : affine.c affine.h eligible.o
	$(CC) $(CFLAGS) affine.c eligible.o -o $(TARGET)

eligible.o : eligible.c affine.h
	$(CC) $(CFLAGS) -c eligible.c

clean :
	rm $(TARGET) eligible.o
