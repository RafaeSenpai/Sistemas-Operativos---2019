#
# Makefile  
#
# Sistemas Operativos - MIEI - 2018/2019
#

CC = gcc
CFLAGS = -Wall

all: cleanExecs ma sv ag cv


ma: ma.o api.o notifications.o
	$(CC) $(CFLAGS) -o ma	ma.o api.o notifications.o

#Agregador -> Cliente de vendas <-> Servidor de vendas
sv: sv.o ag.o api.o notifications.o
	$(CC) $(CFLAGS) -o sv 	sv.o api.o notifications.o

ag: ag.o api.o notifications.o 
	$(CC) $(CFLAGS) -o ag 	ag.o api.o notifications.o

cv: cv.o api.o notifications.o 
	$(CC) $(CFLAGS) -o cv	cv.o api.o notifications.o





ma.o: ma.c  
	$(CC) $(CFLAGS) -c ma.c

cv.o: cv.c 
	$(CC) $(CFLAGS) -c cv.c

ag.o: ag.c
	$(CC) $(CFLAGS) -c ag.c

sv.o: sv.c 
	$(CC) $(CFLAGS) -c sv.c

api.o: api.c api.h
	$(CC) $(CFLAGS) -c api.c

notifications.o: notifications.c notifications.h 
	$(CC) $(CFLAGS) -c notifications.c



cleanExecs: 
	rm -rf ma cv sv ag *.o

cleanData:
	rm -rf strings stocks artigos vendas

cleanAll:
	rm -rf ma cv sv ag *.o strings stocks artigos vendas