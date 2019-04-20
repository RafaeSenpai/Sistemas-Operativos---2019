#ifndef maPARSERS_h
#define maPARSERS_h
#include <ctype.h> //isdigit
#include <stdlib.h> //atof
#include <string.h> //strlen
#include <unistd.h> //system calls
#include <stdio.h>

char* remSpc(char* buffer);
char* takeIDBuff(char* buff);
char takeInstBuff(char* buffer);
char* takeNomeBuff(char* buffer);
char* takePrecoBuff(char* buffer);


#endif