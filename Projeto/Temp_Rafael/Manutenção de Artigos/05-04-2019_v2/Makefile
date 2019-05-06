#
# Makefile  
#
# Sistemas Operativos - MIEI - 2018/2019
#

CC = gcc
CFLAGS = -Wall

all: ma sv ag cv


ma: ma.o maAPI.o notifications.o
	$(CC) $(CFLAGS) -o ma	ma.o maAPI.o notifications.o

#Agregador -> Cliente de vendas <-> Servidor de vendas
sv: ag.o sv.o cv.o notifications.o
	$(CC) $(CFLAGS) -o sv 	ag.o sv.o cv.o notifications.o

ag: ag.o notifications.o 
	$(CC) $(CFLAGS) -o ag 	ag.o notifications.o

cv: cv.o notifications.o ag.o
	$(CC) $(CFLAGS) -o cv	cv.o notifications.o ag.o






ag.o: ag.c ag.h
	$(CC) $(CFLAGS) -c ag.c

ma.o: ma.c  
	$(CC) $(CFLAGS) -c ma.c

maAPI.o: maAPI.c maAPI.h 
	$(CC) $(CFLAGS) -c maAPI.c

notifications.o: notifications.c notifications.h 
	$(CC) $(CFLAGS) -c notifications.c

cv.o: cv.c cv.h
	$(CC) $(CFLAGS) -c cv.c

sv.o: sv.c sv.h
	$(CC) $(CFLAGS) -c sv.c


cleanData:
	rm -rf *.txt

cleanAll:
	rm -rf gestVendas ma cv sv ag *.o *.txt