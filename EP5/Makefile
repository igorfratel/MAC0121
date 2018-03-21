CC = gcc

CFLAGS  = -Wall -ansi -pedantic -g -O2

TARGET = ep5

all: $(TARGET)

$(TARGET): hex.c boardManipulation.o boardManipulation.h strategy.o strategy.h queue.o queue.h linkedList.o linkedList.h
	$(CC) $(CFLAGS) -o $(TARGET) hex.c boardManipulation.o strategy.o queue.o linkedList.o

boardManipulation.o: boardManipulation.c
	$(CC) $(CFLAGS) -c boardManipulation.c

strategy.o: strategy.c
	$(CC) $(CFLAGS) -c strategy.c

queue.o : queue.c
	$(CC) $(CFLAGS) -c queue.c	

linkedList.o : linkedList.c
	$(CC) $(CFLAGS) -c linkedList.c	

clean:
	$(RM) $(TARGET) *.o *~
