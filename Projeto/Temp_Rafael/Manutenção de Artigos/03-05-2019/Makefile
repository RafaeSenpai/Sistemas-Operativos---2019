#
# Makefile  
#
# Sistemas Operativos - MIEI - 2018/2019
#

CC = gcc
CFLAGS = -Wall

all: gestVendas   

gestVendas: ma.o maAPI.o notifications.o cv.o sv.o
	$(CC) $(CFLAGS) -o gestVendas  ma.o maAPI.o notifications.o cv.o sv.o


ma.o: ma.c  
	$(CC) $(CFLAGS) -c ma.c

maAPI.o: maAPI.c maAPI.h 
	$(CC) $(CFLAGS) -c maAPI.c

notifications.o: notifications.c notifications.h 
	$(CC) $(CFLAGS) -c notifications.c

cv.o: cv.c cv.h
	$(CC) $(CFLAGS) -c cv.c

sv.o: sv.c
	$(CC) $(CFLAGS) -c sv.c


cleanData:
	rm -rf *.txt

cleanAll:
	rm -rf gestVendas *.o ma cv sv *.txt