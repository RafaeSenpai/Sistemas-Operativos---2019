#include "cvAPI.h"

/*
	Estrutura do artigo no ficheiro artigos
*/
struct ArtigoF
{
    int id;
    int edr_nome; 
    float preco;
};


/*
	Estrutura generica do artigo
*/
struct Artigo{
	int id;
	char* nome;
	float preco;
	int stock;
};




ssize_t cvReadln(int fildes, void *buf, size_t nbyte){
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


void atualizaStock(char* cod, char* qt){ //---------------------------------------FUNCIONAL
int fdSTK = open("STOCKS.txt",O_RDWR);
char* msg = malloc(100*sizeof(char));
int qtdAtual = 0;
int newStock = 0;

	if(fdSTK>-1){
		lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
		read(fdSTK,&qtdAtual,sizeof(int));
		
		newStock = qtdAtual + (atoi(qt));
		lseek(fdSTK,(-1)*sizeof(int),SEEK_CUR);//<--- reposicionamento para o local onde se quer colocar o stock atualizado
		write(fdSTK,&newStock,sizeof(int));
		close(fdSTK);
		if(msg){
			sprintf(msg,"Novo stock: %d\n",newStock);
			write(1,msg,strlen(msg));
			free(msg);
		}else{
			catchError(ERROR_12);
		}
	}else{
		catchError(ERROR_9);
	}
}



/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
void cvGetStock(char* id){ //-------------------------------------------------------FUNCIONAL
int fdStK = open("STOCKS.txt", O_RDONLY);
char* msg = malloc(100*sizeof(char));
int stk;

	if(fdStK){
		lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
		read(fdStK,&stk,sizeof(int));
		close(fdStK);
		if(msg){
			sprintf(msg,"Stock: %d\n",stk);	
			write(1, msg, strlen(msg));
			free(msg);
		}else{
			catchError(ERROR_13);
		}
	}else{
		catchError(ERROR_10);
	}
}


/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
void getPreco(char* id){//-------------------------------------------------------FUNCIONAL
int fdART = open("ARTIGOS.txt",O_RDWR);
char* msg = malloc(100*sizeof(char));
float catchincatchin;

	if(fdART){
		lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
		read(fdART,&catchincatchin,sizeof(float));
		close(fdART);
		if(msg){
			sprintf(msg,"Preço: %.2f\n",catchincatchin);
			write(1,msg,strlen(msg));
			free(msg);
			}else{
				catchError(ERROR_14);
			}
	}else{
		catchError(ERROR_11);
	}
}



void getStockAndPrice(char* id){ //---------------------------------------------FUNCIONAL

	cvGetStock(id);
	getPreco(id);
}


void cvMenuComandos(char* buffer){//----------------------------------------------FUNCIONAL
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
int countParams = 0;

	
	while(countParams==0){
		if(param1 && param2){
			countParams = 2;
		}else if(param1 || param2){
			countParams = 1;				
		}
	}

	switch(countParams){
		case 1:
			/*<código_numérico> --> mostra no stdout stock e preço*/
			getStockAndPrice(param1);
			write(1,"\n\n",1);
			break;
		case 2:
			/*<código_numérico> <quantidade> --> actualiza stock e mostra novo stock*/
			atualizaStock(param1,param2);
			write(1,"\n\n",2);
			break;
		default:
			system("clear");
			write(1,"Opção inválida!\nInsira novo comando:\n",41);
	}

}