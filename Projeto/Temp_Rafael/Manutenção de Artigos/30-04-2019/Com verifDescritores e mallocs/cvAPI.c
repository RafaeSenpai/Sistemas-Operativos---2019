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


/*
	Estrutura de uma Venda no ficheiro Vendas
*/
struct Vendas{
	int idArt;
	float quant;
	float vTotal;
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


Venda criaStructVenda(char* idArt, char* quant){
Venda newSale = malloc(sizeof(struct Vendas));

	if(newSale){
		newSale->idArt = atoi(idArt);
		newSale->quant = (-1) * atoi(quant);//<---não faz sentido guardar numa venda o valor que foi subtraido ao stock do produto, mas sim a quantidade que foi vendida (valor positivo)
		newSale->vTotal = (-1) * atof(quant) * (getPreco(idArt));
		return newSale;
	}else{
		catchError(ERROR_25);
	}
	return NULL;
}


void atualizaStock(char* cod, char* qt){
int fdSTK = open("STOCKS.txt",O_RDWR);
int fdVendas = open("VENDAS.txt",O_CREAT | O_RDWR | O_APPEND,0777);
char* msg = malloc(100*sizeof(char));
int qtdAtual = 0;
int newStock = 0;


	if(fdSTK>-1){
		if(fdVendas>-1){
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

				if(atoi(qt)<0){	
					Venda sale = criaStructVenda(cod,qt);
					lseek(fdVendas,sizeof(struct Vendas),SEEK_END);
					write(fdVendas,sale,sizeof(struct Vendas));
					viewVenda(sale);
					close(fdVendas);
				}
			}else{
				catchError(ERROR_12);
			}
		}else{
			catchError(ERROR_24);
		}
	}else{
		catchError(ERROR_9);
	}
}




Venda getVenda(char* x){
int fdVendas = open("VENDAS.txt",O_RDONLY);
Venda sale = NULL;

	if(fdVendas){
		int nbEnd = lseek(fdVendas,0,SEEK_END); //numero de bytes existentes ate ao final do ficheiro
		int nbLocal = lseek(fdVendas,atoi(x)*sizeof(struct Vendas),SEEK_SET);	//numero de bytes até á estrutura que se quer ler
		sale = malloc(sizeof(struct Vendas));
		if(sale){
			if(nbLocal<nbEnd){//se o "numero" da venda a procurar não existir retorna NULL
				lseek(fdVendas,atoi(x)*sizeof(struct Vendas),SEEK_SET);	
				read(fdVendas,sale,sizeof(struct Vendas));
				close(fdVendas);
				//não posso fazer free snao perco a informação que quero devolver
				return sale;
			}else{
				return NULL;
			}
		}else{
			catchError(ERROR_27);
		}
	}else{
		catchError(ERROR_26);
	}
return NULL;
}


void viewVenda(Venda sale){
char* msg = malloc(150*sizeof(char));
	if(sale){
		if(msg){
			sprintf(msg,"\nVenda inserida:\n    End. MEMORIA da struct apresentada: %p\n    ID artigo: %d\n    Quantidade: %.0f\n    Valor Total: %.2f\n\n",sale,sale->idArt,sale->quant,sale->vTotal);
			write(1,msg,strlen(msg));
			free(msg);
		}else{
			catchError(ERROR_28);
		}
	}else{
		free(sale);
		write(1,"Não existe a venda pedida!\n",28);
	}
}

/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
int cvGetStock(char* id){ //-------------------------------------------------------FUNCIONAL
int fdStK = open("STOCKS.txt", O_RDONLY);
int stk;

	if(fdStK){
		lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
		read(fdStK,&stk,sizeof(int));
		close(fdStK);
		return stk;
	}else{
		catchError(ERROR_10);
	}
	return 0;
}


/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
float getPreco(char* id){
int fdART = open("ARTIGOS.txt",O_RDWR);
float catchincatchin;

	if(fdART){
		lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
		read(fdART,&catchincatchin,sizeof(float));
		close(fdART);
		return catchincatchin;
	}else{
		catchError(ERROR_11);
	}
	return 0;
}



void getStockAndPrice(char* id){ //---------------------------------------------FUNCIONAL
char* msg = malloc(100 * sizeof(char));
	
	sprintf(msg,"Stock: %d\nPreço: %.2f\n\n",cvGetStock(id),getPreco(id));
	write(1,msg,strlen(msg));
}


void cvMenuComandos(char* buffer){//----------------------------------------------FUNCIONAL
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
int countParams = 0;
char* x = "gv";
	
	while(countParams==0){		
		if(strcmp(param1,x)==0){
			countParams = 3;
		}else{
			if(param1 && param2){
				countParams = 2;
			}else if(param1 || param2){
				countParams = 1;				
			}
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
		case 3:
			/*EXTRA - FUnção usada para confirmar se os dados são corretamente guardados*/
			viewVenda(getVenda(param2));
			write(1,"\n\n",2);
			break;
		default:
			system("clear");
			write(1,"Opção inválida!\nInsira novo comando:\n",41);
	}

}