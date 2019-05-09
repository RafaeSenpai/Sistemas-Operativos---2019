CC = gcc
CFlags = -o

all: ma

teste: ma.o
	$(CC) ma.o  $(CFlags)

ma.o: ma.c
	$(CC) -c ma.c 

sv: sv.c
    $(CC) sv $(CFlags)

cv: cv.c
    $(CC) $(CFlags) cv

clean:
	rm /tmp/client_to_server /tmp/W* /tmp/R* 


txt:
	rm -rf *.txt

run:
	./ma
