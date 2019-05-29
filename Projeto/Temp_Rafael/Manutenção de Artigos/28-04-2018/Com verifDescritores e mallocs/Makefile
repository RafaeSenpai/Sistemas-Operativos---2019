#
# Makefile  
#
# Sistemas Operativos - MIEI - 2018/2019
#

CC = gcc
CFLAGS = -Wall

all: gestVendas   

gestVendas: ma.o maAPI.o errors.o cv.o cvAPI.o
	$(CC) $(CFLAGS) -o gestVendas  ma.o maAPI.o errors.o cv.o cvAPI.o


ma.o: ma.c  
	$(CC) $(CFLAGS) -c ma.c

maAPI.o: maAPI.c maAPI.h 
	$(CC) $(CFLAGS) -c maAPI.c

errors.o: errors.c errors.h 
	$(CC) $(CFLAGS) -c errors.c

cv.o: cv.c
	$(CC) $(CFLAGS) -c cv.c

cvAPI.o: cvAPI.c cvAPI.h 
	$(CC) $(CFLAGS) -c cvAPI.c


cleanMa:
	rm -rf ma.o maAPI.o errors.o

cleanCv:
	rm -rf cv.o cvAPI.o errors.o

cleanData:
	rm -rf STRINGS.txt STOCKS.txt ARTIGOS.txt VENDAS.txt

cleanAll:
	rm -rf ma.o maAPI.o cv.o cvAPI.o errors.o STRINGS.txt STOCKS.txt ARTIGOS.txt VENDAS.txt