#
# Makefile  
#
# Sistemas Operativos - MIEI - 2018/2019

CC = gcc
CFLAGS = -Wall




all: gestVendas   
gestVendas: ma.o maMenu.o maAPI.o maPARSERS.o cv.o cvMenu.o cvAPI.o
	$(CC) $(CFLAGS) -o gestVendas  ma.o maMenu.o maAPI.o maPARSERS.o cv.o cvMenu.o cvAPI.o

cv: clienteVendas
clienteVendas: cv.o cvMenu.o cvAPI.o
	$(CC) $(CFLAGS) -o clienteVendas  cv.o cvMenu.o cvAPI.o

ma: manutencaoArtg
manutencaoArtg: ma.o maMenu.o maAPI.o maPARSERS.o
	$(CC) $(CFLAGS) -o manutencaoArtg  ma.o maMenu.o maAPI.o maPARSERS.o





ma.o: ma.c  
	$(CC) $(CFLAGS) -c ma.c

maMenu.o: maMenu.c maMenu.h 
	$(CC) $(CFLAGS) -c maMenu.c

maAPI.o: maAPI.c maAPI.h 
	$(CC) $(CFLAGS) -c maAPI.c

maPARSERS.o: maPARSERS.c maPARSERS.h 
	$(CC) $(CFLAGS) -c maPARSERS.c

cv.o: cv.c
	$(CC) $(CFLAGS) -c cv.c

cvMenu.o: cvMenu.c cvMenu.h 
	$(CC) $(CFLAGS) -c cvMenu.c

cvAPI.o: cvAPI.c cvAPI.h 
	$(CC) $(CFLAGS) -c cvAPI.c






cleanMa:
	rm -rf ma.o maMenu.o maAPI.o maPARSERS.o 

cleanCv:
	rm -rf cv.o cvMenu.o cvAPI.o

cleanData:
	rm -rf STRINGS.txt STOCKS.txt ARTIGOS.txt VENDAS.txt

cleanAll:
	rm -rf ma.o maMenu.o maAPI.o maPARSERS.o cv.o cvMenu.o cvAPI.o STRINGS.txt STOCK.txt ARTIGOS.txt VENDAS.txt