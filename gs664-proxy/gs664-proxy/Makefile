#Sample Makefile. You can make changes to this file according to your need
# The executable must be named proxy

CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = proxy.o csapp.o

all: proxy

proxy: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o proxy

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

proxy2.o: proxy.c
	$(CC) $(CFLAGS) -c proxy.c

clean:
	rm -f *~ *.o proxy 

