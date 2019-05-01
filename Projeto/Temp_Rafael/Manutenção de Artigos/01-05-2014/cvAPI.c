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
		
		if(atoi(quant)<0){
			newSale->quant = (-1) * atoi(quant);//<---não faz sentido guardar numa venda o valor que foi subtraido ao stock do produto, mas sim a quantidade que foi vendida (valor positivo)
			newSale->vTotal = (-1) * atof(quant) * (getPreco(idArt));
		}else{
			newSale->quant = atoi(quant);
			newSale->vTotal = atof(quant) * (getPreco(idArt));
		}
		return newSale;
	
	}else{
		catchMessage(ERROR_25);
	}

	return NULL;
}


void atualizaStock(char* cod, char* qt){
int fdSTK = open("STOCKS.txt",O_RDWR);
int qtdAtual = 0;
int newStock = 0;


	if(fdSTK>-1){
		int nbLocal = lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
		int nbEnd = lseek(fdSTK,0,SEEK_END);
		
		if(nbLocal<nbEnd){
			int fdVendas = open("VENDAS.txt",O_CREAT | O_RDWR | O_APPEND,0777);
			
			if(fdVendas>-1){
				lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
				read(fdSTK,&qtdAtual,sizeof(int));
				newStock = qtdAtual + (atoi(qt));
				
				if(newStock>=0){ //<<<-----------------------Verifica se ao validar a venda se o stock fica negativo! se nao ficar a negativo atualiza o stock e regista a venda
					lseek(fdSTK,(-1)*sizeof(int),SEEK_CUR);//<----------------------- reposicionamento para o local onde se quer colocar o stock atualizado
					write(fdSTK,&newStock,sizeof(int));
					close(fdSTK);
					char* msg = malloc(100*sizeof(char));

					if(msg){
						sprintf(msg,"Stock atual: %d\n",newStock);
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
						close(fdVendas);
						catchMessage(ERROR_12);
					}

				}else{//<<<<-----------------------se ao validar a encomenda o stock ficar a negativo, é vendido todo o stock existente, criada a venda e zerado o stock do artigo
					lseek(fdSTK,(-1)*sizeof(int),SEEK_CUR);//<-----------------------(ATUALIZAÇÃO DO STOCK) reposicionamento para o local onde se quer colocar o stock atualizado
					

					int x = 0;
					char* zero = malloc(2*sizeof(char));

					sprintf(zero,"%d",x);
					write(fdSTK,&x,sizeof(int));
					close(fdSTK);

					

					char* strqt = malloc(50*sizeof(char));
					sprintf(strqt,"%d",qtdAtual);
					Venda sale = criaStructVenda(cod,strqt);//<<--- VENDO TODO O STOCK EXISTENTE e mult por (-1) porque o 2º param passado á função criaStructVenda já está a multiplicar por (-1) para que as vendas nao apresentem vendas de stocks negativos
					
					

					lseek(fdVendas,sizeof(struct Vendas),SEEK_END);
					write(fdVendas,sale,sizeof(struct Vendas));//<<---- guardo a venda
					viewVenda(sale);
					close(fdVendas);

					char* msg = malloc(100*sizeof(char));
						
					if(msg){
						sprintf(msg,"Não foi possivel a venda de %d unidades!\n",(-1)*(atoi(qt) + qtdAtual));
						write(1,msg,strlen(msg));
						free(msg);
						catchMessage(MSG_9);
					}else{
						catchMessage(ERROR_15);
					}
				}

			}else{
				catchMessage(ERROR_24);
			}

		}else{
			close(fdSTK);
			catchMessage(MSG_2);
			//exit(0);// <-------------------------------------------------------------------------------------pode vir a gerar problemas aqui por causa do exit(0)
		}

	}else{
		catchMessage(ERROR_9);
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
				close(fdVendas);
				return NULL;
			}

		}else{
			close(fdVendas);
			catchMessage(ERROR_27);
		}

	}else{
		catchMessage(ERROR_26);
	}

return NULL;
}


void viewVenda(Venda sale){
char* msg = malloc(150*sizeof(char));

	if(sale){

		if(msg){
			sprintf(msg,"\nVenda inserida:\n    ID artigo: %d\n    Quantidade: %.0f\n    Valor Total: %.2f\n\n",sale->idArt,sale->quant,sale->vTotal);
			write(1,msg,strlen(msg));
			free(msg);
		}else{
			catchMessage(ERROR_28);
		}

	}else{
		free(sale);
		catchMessage(MSG_3);
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
		int nbLocal = lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
		int nbEnd = lseek(fdStK,0,SEEK_END);

		if(nbLocal<nbEnd){
			lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
			read(fdStK,&stk,sizeof(int));
			close(fdStK);
			return stk;
		}else{
			close(fdStK);
			catchMessage(MSG_5);
		}

	}else{
		catchMessage(ERROR_10);
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
		int nbLocal = lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
		int nbEnd = lseek(fdART,0,SEEK_END);

		if(nbLocal<nbEnd){
			lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
			read(fdART,&catchincatchin,sizeof(float));
			close(fdART);
			return catchincatchin;
		}else{
			close(fdART);
			catchMessage(MSG_6);
		}

	}else{
		catchMessage(ERROR_11);
	}
	return 0;
}



void getStockAndPrice(char* id){ //---------------------------------------------FUNCIONAL
char* msg = malloc(100 * sizeof(char));
int fdART = open("ARTIGOS.txt",O_RDWR);

	if(fdART){
		int nbLocal = lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
		int nbEnd = lseek(fdART,0,SEEK_END);
		
		if(nbLocal<nbEnd){
			sprintf(msg,"Stock: %d\nPreço: %.2f\n\n",cvGetStock(id),getPreco(id));
			write(1,msg,strlen(msg));
			close(fdART);
		}else{
			close(fdART);
			catchMessage(MSG_1);
		}

	}else{
		catchMessage(ERROR_11);
	}
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
			catchMessage(MSG_4);
	}

}