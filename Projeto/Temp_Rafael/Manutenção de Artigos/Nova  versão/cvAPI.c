#include "cvAPI.h"

ssize_t readln(int fildes, void *buf, size_t nbyte){
int n;
char c;
char *buffer = (char *)buf;
ssize_t nbytes = 0;


    
    while( nbytes < nbyte && (n = read(fildes,&c,1)) > 0 && c != '\n' ){
        buffer[nbytes++] = c;
    }
    

    if(nbytes < nbyte){
    	(buffer[nbytes] = '\0');
    }else{
    	(buffer[nbytes-- - 1] = '\0');
    }
    
    return nbytes;
}


void atualizaStock(char* cod, char* qt){
int fdSTK = open("STOCKS.txt",O_RDWR);

	lseek(fdSTK, atoi(cod)*sizeof(struct Stock) + sizeof(int),SEEK_SET);
	//char *qtd = malloc(sizeof(char) * 30);
	//sprintf(qtd,"%d",atoi(qt));
	//int x = atoi(qt);
	write(fdSTK, qt,sizeof(int));
	write(1,qt,strlen(qt));
	close(fdSTK);

}


int getStock(char* id){
int fdStK = open("STOCKS.txt", O_RDONLY);
Stock stk = malloc(sizeof(struct Stock));

	lseek(fdStK,atoi(id)*sizeof(struct Stock),SEEK_SET);
	read(fdStK,stk,sizeof(struct Stock));
	printf("STOCK DEVOLVIDO:%d\n",stk->stock);

	return stk->stock;
}