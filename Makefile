CC = gcc 
CFLAGS = -Wall -Werror -g

all: count

count: count.c
	$(CC) $(CFLAGS) -o count count.c 

clean:
	rm -f count
