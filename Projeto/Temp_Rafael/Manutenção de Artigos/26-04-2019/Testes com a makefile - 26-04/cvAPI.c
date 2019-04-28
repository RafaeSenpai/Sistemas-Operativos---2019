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


void atualizaStock(char* cod, char* qt){ //-------------------------nao parece que esteja a guardar diretio
int fdSTK = open("STOCKS.txt",O_RDWR);

	lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
	
	char *qtd = malloc(sizeof(char) * 30);
	sprintf(qtd,"%d",atoi(qt));
	
	write(fdSTK, qtd,sizeof(int));
	write(1,qtd,sizeof(int));
	close(fdSTK);

}



/*
	FUnção responsavel por devolver o valor do stock de um artigo com um dado ID
	NOTA: não imprime nada no terminal, apenas retorna o valor do stock
*/
int getStock(char* id){ //------------------------------------------------------------------funciona direito
int fdStK = open("STOCKS.txt", O_RDONLY);
int stk;

	lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
	read(fdStK,&stk,sizeof(int));	
	close(fdStK);

	return stk; //retorna o stock para o caso de dar jeito usar um output valido da função 
}



void getStockAndPrice(char* id){ //--------------------------------INCOMPLETO
int fdStK = open("STOCKS.txt", O_RDONLY);
int stk;

	lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
	read(fdStK,&stk,sizeof(int));

	char *qtd = malloc(sizeof(char) * 30);
	sprintf(qtd,"%d",stk);//escrve o stk para string
	write(1,qtd,sizeof(int)); //imprime no ecra o stock
	
	close(fdStK);
}