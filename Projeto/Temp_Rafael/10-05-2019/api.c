#include <fcntl.h> //file descriptor
#include <unistd.h> //system calls
#include <time.h>
#include <stdlib.h> //atof exit()
#include <string.h> //strlen - strcpy - strtok - strcmp
#include <stdio.h> //sprintf
#include "api.h"
#include "notifications.h"

#define ArtgsFile "artigos"
#define SaleFile "vendas"
#define StockFile "stocks"
#define StringFile "strings"
#define LogFileLocal "Ficheiro_Log"


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


/*
	EStrutura que integra o ficheiro log
*/
struct Log{
	char nameFile[50];
	int status;
	int lastAggregateSale;
};





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



//--------------------------------------------------API AGREGADOR -----------------------------------
char* nameFileAggregation(){//----------------------------------------------------------------------------OPERACIONAL
time_t data;
data = time(NULL);
char* nametoAgregationFile = malloc(50*sizeof(char));
int x;
	
	if(nametoAgregationFile){
	    strcat(nametoAgregationFile,ctime(&data));
	    x = strlen(nametoAgregationFile) - 1;
	    nametoAgregationFile[x]='\0';
	    return nametoAgregationFile;
	}else{
		catchMessage(ERROR_31);
		return NULL;
	}
}

int getNumVendas(int fd){ //-------------------------------------------------------------------------------------OPERACIONAL
int totBytes;
	if(fd){
		totBytes = lseek(fd,0,SEEK_END);
		close(fd);
		return totBytes/(sizeof(struct Vendas));
	}else{
		catchMessage(ERROR_46);
	}
	return -1;

}






void seeAllAggregation(int fd, int nArtInAgg){

Venda sale = malloc(sizeof(struct Vendas));
int i;
	
	for(i=0; i<nArtInAgg;){//<-----enquanto nao encontrar o numero de artigos no ficheiro de agregação repete o processo
		if((read(fd,sale,sizeof(struct Vendas)))!=0){//se ler alguma venda da posição corrente
			i++;
			viewVenda(sale);
		}
	}
}







int runAggregation(){//----------------------------------------------------------------------------------------OPERACIONAL
	int fdLog = open(LogFileLocal,O_CREAT | O_RDWR,0777);
	int fdAgg = open(nameFileAggregation(),O_CREAT | O_RDWR,0777);
	int fdSales = open(SaleFile, O_RDONLY,0777);
	int nLastSaleAgg = 0;
	int nArtInAgg=0;//usado para contabilizar o numero de artigos inseridos no ficheiro de agregação
	int b;

	write(fdLog,&nLastSaleAgg,sizeof(int));//dá indicação de que a ultima venda agregada foi a venda na posiçao 0 do ficheiro vendas
	
	printf("ULTIMA VENDA ADICIONADA");
	if(fdLog>-1){
		read(fdLog,&nLastSaleAgg,sizeof(int));//lê do log para nLastSaleAgg a ultima posição agregada do ficheiro vendas
		if(fdSales>-1){
			Venda sale = malloc(sizeof(struct Vendas));
			Venda saleVendas = malloc(sizeof(struct Vendas));
			if(sale){
				if(fdAgg>-1){
					lseek(fdSales,nLastSaleAgg*sizeof(struct Vendas),SEEK_SET);//posiciona-se na respetiva venda e guarda para uma estrutura

					while(read(fdSales,sale,sizeof(struct Vendas))>0){ //enquanto houver vendas o ciclo vai-se repetindo

						lseek(fdAgg, (sale->idArt)*sizeof(struct Vendas),SEEK_SET);//posiciona-se no preciso local no ficheiro de agregação
						b = read(fdAgg,saleVendas,sizeof(struct Vendas));
					
						if(b == 0){//<----se não existir nada nessa posição um registo entao
							write(fdAgg,sale, sizeof(struct Vendas));//----regista a venda como foi capturada do ficheiro vendas
							nArtInAgg++;//atualiza o numero de artigos adicionados ao ficheiro de agregação
						}else{//<<---- caso ja exista uma venda entao são somados os valores capturados anteriormente á estrutura já existente na posição no agregador
							sale->quant += saleVendas->quant;
							sale->vTotal += saleVendas->vTotal;
							lseek(fdAgg,(sale->idArt) * sizeof(struct Vendas),SEEK_SET);
							write(fdAgg,sale,sizeof(struct Vendas));
							//memset(saleVendas,0,sizeof(struct Vendas));
						}
						nLastSaleAgg++;//atualiza o numero da posição do artigo no ficheiro vendas que foi tratado para agregação
						lseek(fdLog,0,SEEK_SET);
						write(fdLog,&nLastSaleAgg,sizeof(int));																					
					}
					free(sale);
					close(fdSales);
					close(fdLog);
					lseek(fdAgg,0,SEEK_SET);//reposiciona o descritor de ficheiros para o inicio
					

					seeAllAggregation(fdAgg, nArtInAgg);
					
					return fdAgg;

				}else{
					free(sale);
					close(fdSales);
					close(fdLog);	
				}

			}else{
				close(fdSales);
				close(fdLog);
			}
		}else{
			close(fdLog);
		}
	}
	return -1;
}



/*
int main(){
char buffer[1024];
Venda sale = malloc(sizeof(struct Vendas));
int tmpFile = open("tmp",O_CREAT,O_RDWR,0777);
		
//		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	

	while(read(0,&sale,sizeof(struct vendas))){
		write(tmpFile,sale,sizeof(struct Vendas));
	}

return 0;
}

*/


void gerarAgregacao(){

/*	Venda sale = malloc(sizeof(struct Vendas));
	int tmpFile = open("tmp",O_CREAT,O_RDWR,0777);
*/	/*	
		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	*/
/*
	while(read(0,&sale,sizeof(struct Vendas))){
		write(tmpFile,sale,sizeof(struct Vendas));
	}
close(tmpFile);
free(sale);
*/
runAggregation();
}
	
//----------------FIM API AGREGADOR -----------------------






//----------------API Cliente de Vendas -------------------
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
int fdSTK = open(StockFile,O_RDWR);
int qtdAtual = 0;
int newStock = 0;


	if(fdSTK>-1){
		int nbLocal = lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
		int nbEnd = lseek(fdSTK,0,SEEK_END);
		
		if(nbLocal<nbEnd){
			int fdVendas = open(SaleFile,O_CREAT | O_RDWR | O_APPEND,0777);
			
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
					if(qtdAtual>0){
						sprintf(strqt,"%d",qtdAtual);
						Venda sale = criaStructVenda(cod,strqt);//<<--- VENDO TODO O STOCK EXISTENTE e mult por (-1) porque o 2º param passado á função criaStructVenda já está a multiplicar por (-1) para que as vendas nao apresentem vendas de stocks negativos
						
						lseek(fdVendas,sizeof(struct Vendas),SEEK_END);
						write(fdVendas,sale,sizeof(struct Vendas));//<<---- guardo a venda
						viewVenda(sale);
					}

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
int fdVendas = open(SaleFile,O_RDONLY);
Venda sale = NULL;

	if(fdVendas){
		int nbEnd = lseek(fdVendas,0,SEEK_END); //numero de bytes existentes ate ao final do ficheiro
		int nbLocal = lseek(fdVendas,atoi(x)*sizeof(struct Vendas),SEEK_SET);	//numero de bytes até á estrutura que se quer ler
		sale = malloc(sizeof(struct Vendas));
		
		if(sale){

			if(nbLocal<nbEnd){//se o "numero" da venda a procurar não existir retorna NULL
				if(atoi(x)>=0){	
					lseek(fdVendas,atoi(x)*sizeof(struct Vendas),SEEK_SET);	
					read(fdVendas,sale,sizeof(struct Vendas));
					close(fdVendas);
					//não posso fazer free snao perco a informação que quero devolver
					return sale;
				}else{
					close(fdVendas);
					catchMessage(MSG_1);
				}
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


float getPreco(char* id){
int fdART = open(ArtgsFile,O_RDWR);
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



void getStockAndPrice(char* id){
char* msg = malloc(100 * sizeof(char));
int fdART = open(ArtgsFile,O_RDWR);

	if(atoi(id)>=0){		
		if(fdART){
			int nbLocal = lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
			int nbEnd = lseek(fdART,0,SEEK_END);
			
			if(nbLocal<nbEnd){
				sprintf(msg,"Stock: %d\nPreço: %.2f\n\n",getStock(atoi(id)),getPreco(id));
				write(1,msg,strlen(msg));
				close(fdART);
			}else{
				close(fdART);
				catchMessage(MSG_1);
			}

		}else{
			catchMessage(ERROR_11);
		}
	}else{
		catchMessage(MSG_1);
	}
}

//-----------------FIM API Cliente de Vendas -----------------------












//-----------------API  Manuetenção de Artigos ---------------------

ArtigoFile criaStructArtigo(int nbArt, int nbStr,char* price){
ArtigoFile new = malloc(sizeof(struct ArtigoF));
	
	if(new){
		new->id = nbArt/sizeof(struct ArtigoF);
		new->edr_nome = nbStr;
		new->preco = atof(price);
		return new;
	}else{
		catchMessage(ERROR_16);
	}
	return NULL;
}


void insereArtigo(char* nome,char* preco){
	int fdStr = open(StringFile, O_CREAT |O_RDWR, 0777);
	int nbStr;
	
	if(fdStr>-1){ 
		nbStr = lseek(fdStr,0,SEEK_END); 
		write(fdStr,nome,strlen(nome));
		write(fdStr,"\n",sizeof(char));
		close(fdStr);
	}else{
		catchMessage(ERROR_1);
	}

	int fdArt = open(ArtgsFile, O_CREAT |O_RDWR, 0777);
	if(fdArt>-1){
		int nbArt = lseek(fdArt,0,SEEK_END);

		ArtigoFile newArt = criaStructArtigo(nbArt,nbStr,preco);	

		write(fdArt,newArt,sizeof(struct ArtigoF)); 
		char *id = malloc(sizeof(char) * 30);
		
		if(id){
			sprintf(id,"%d",newArt->id);
			write(1,id,sizeof(int));//<---provavelmente dará problemas aquando houver IDs com mais que 4 caracteres
			free(id);
		}else{
			catchMessage(ERROR_18);
		}
		close(fdArt);
		free(newArt);
	
	}else{
		catchMessage(ERROR_2);
	}

	int quant = 0;
	int fdStK = open(StockFile, O_CREAT | O_RDWR | O_APPEND, 0777);
	
	if(fdStK>-1){
		write(fdStK,&quant,sizeof(int));
		close(fdStK);
	}else{
		catchMessage(ERROR_3);
	}
}




char* getNome(int edr_nome){
int fdStr = open(StringFile, O_RDONLY, 0777);
	if(fdStr>-1){
		char* nome = malloc(100*sizeof(char));
		
		if(nome){
			lseek(fdStr,edr_nome,SEEK_SET);
			readln(fdStr,nome,100); //se colocar no lugar do 100, strlen(nome) o nome do artigo deixa de aparecer
			close(fdStr);
			//Não posso fazer free do malloc desta função porque não perco a informação que quero retornar
			return nome;
		}else{
			close(fdStr);
			catchMessage(ERROR_19);
		}

	}else{
		catchMessage(ERROR_4);
	}

	return NULL;
}


int getStock(int id){
int fdStK = open(StockFile, O_RDONLY, 0777);
	
	if(fdStK>-1){
		int nbEnd = lseek(fdStK,0,SEEK_END);
		int nbLocal = lseek(fdStK,id*sizeof(int),SEEK_SET);
	
		if(nbLocal<nbEnd){
			int stk = 0;
			lseek(fdStK,id*sizeof(int),SEEK_SET);
			read(fdStK,&stk,sizeof(int));
			close(fdStK);
			return stk;
		}else{
			close(fdStK);
			catchMessage(MSG_5);
		}
	
	}else{
		catchMessage(ERROR_5);
	}

return 0;
}



void viewArtigo(Artigo art){
char* msg = malloc(200*sizeof(char));
	
	if(art){
	
		if(msg){
			write(1,"-----------------FICHA DE ARTIGO-----------------\n",50);
			sprintf(msg,"ID: %d\nNome: %s\nPreço: %.2f\nStock: %d\n",art->id,art->nome,art->preco,art->stock);
			write(1, msg,strlen(msg));
			write(1,"-------------------------------------------------\n",50);
			free(msg);
		}else{
			catchMessage(ERROR_20);
		}

	}else{
		catchMessage(MSG_1);
	}
}


Artigo getArtigo(char* id){
int fdArt = open(ArtgsFile, O_RDONLY, 0777);
	
	if(fdArt>-1){
		
		if(atoi(id)>=0){
			int nbEnd = lseek(fdArt,0,SEEK_END);//numero de bytes existentes ate ao final do ficheiro
			int nbAtual = lseek(fdArt,(atoi(id))*sizeof(struct ArtigoF),SEEK_SET); //numero de bytes até á estrutura que se quer ler
			
			if(nbAtual<nbEnd){
				ArtigoFile newArtF = malloc(sizeof(struct ArtigoF));
				
				if(newArtF){
					read(fdArt,newArtF,sizeof(struct ArtigoF));
					Artigo art = malloc(sizeof(struct Artigo));
					
					if(art){
						art->id = newArtF->id;
						art->nome = getNome(newArtF->edr_nome);
						art->preco = newArtF->preco;
						art->stock = getStock(newArtF->id);
						free(newArtF);
						close(fdArt);
						/*
							Não posso fazer free do malloc (art) desta função porque snão perco a informação que quero 
							retornar, mas em contra partida quando faço get de uma artigo que nao existe este devolve-me 
							parte da informação relativa a um artigo existente
						*/
						return art;
					
					}else{
						catchMessage(ERROR_23);
					}	
				
				}else{
					close(fdArt);
					catchMessage(ERROR_21);
				}
			
			}else{
				close(fdArt);
				return NULL;
			}
		}else{
			close(fdArt);
			catchMessage(MSG_1);
		}
	
	}else{
		catchMessage(ERROR_6);
	}
	
	return NULL;
}




void editaNome(char* id, char* nome){
int fdSTR = open(StringFile,O_RDWR);

	if(fdSTR>-1){
		int fdART = open(ArtgsFile,O_RDWR);
		
		if(fdART>-1){
			int nbEnd = lseek(fdART,0,SEEK_END); //numero de bytes lidos ate ao final do ficheiro Artigos
			int nbLocal = lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);//Numero de bytes lidos até á inserção do artigo no ficheiro artigos
		
			if(nbLocal<nbEnd){
				strcat(nome, "\n");
				int nbSTR = lseek(fdSTR,0,SEEK_END);
				write(fdSTR, nome,strlen(nome));
				close(fdSTR);
				
				lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int),SEEK_SET);
				write(fdART, &nbSTR, sizeof(int));
				close(fdART);
				
				catchMessage(MSG_7);
				viewArtigo(getArtigo(id));
			}else{
				close(fdART);
				catchMessage(MSG_8);
			}

		}else{
			close(fdART);
			catchMessage(ERROR_14);
		}
			
	}else{
		catchMessage(ERROR_7);
	}
}




void editaPreco(char* id, char* makeItRain){
float catchincatchin;
int fdART = open(ArtgsFile,O_RDWR);
	
	if(fdART>-1){
		int nbEnd = lseek(fdART,0,SEEK_END);
		int nbLocal = lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);

		if(nbLocal<nbEnd){
			lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
			catchincatchin = atof(makeItRain);
			write(fdART, &catchincatchin, sizeof(float));
			close(fdART);
		}else{
			close(fdART);
			catchMessage(MSG_6);
		}
	}else{
		catchMessage(ERROR_8);
	}
}
//---------------FIM API Manutenção de Artigos ------------------














//-----------------------------todos os interpretadores de comandos
//------------------------------------------INTERPRETADOR DE COMANDOS PARA O cliente de vendas e agregação




//CRIAR NO MENU UMA OPÇÃO DE PROJETAR NO TERMINAL O CONTEUDO DO FICHEIRO LOG
//CRIAR NO MENU UMA OPÇÃO DE PROJETAR NO TERMINAL O CONTEUDO DO FICHEIRO LOG
//CRIAR NO MENU UMA OPÇÃO DE PROJETAR NO TERMINAL O CONTEUDO DO FICHEIRO LOG

void menuComandos(char* buffer){
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
int countParams = 0;

	
	while(countParams==0){	

		if(strcmp(param1,"gv") == 0){
			countParams = 4;
		}else if(strcmp(param1,"ag") == 0){
			countParams = 3;
		}else if((strcmp(param1,"log") == 0)){
			countParams = 5;
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
			gerarAgregacao();
			break;
		case 4:
			/*EXTRA - FUnção usada para confirmar se os dados são corretamente guardados*/
			viewVenda(getVenda(param2));
			write(1,"\n\n",2);
			break;
		case 5:
			//seeContentLog();
			break;
		default:
			system("clear");
			catchMessage(MSG_4);
	}

}






//---------------------------------------------INTERPRETADOR DE COMANDOS da Manutenção de artigos--------------------
void maMenuComandos(char* buffer){
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
char* param3 = strtok(NULL," ");
char* msg = malloc(50*sizeof(char));

	switch(*param1){
		case 'i':
			insereArtigo(param2,param3);
			write(1,"\n",1);
			break;
		case 'n':
			/*n <código> <novo nome> --> altera nome do artigo*/
			editaNome(param2,param3);
			write(1,"\n",1);
			break;
		case 'p':
			/*p <código> <novo preço>   --> altera preço do artigo*/
			editaPreco(param2,param3);
			break;
		case 'g':	
			/*g <codigo>  -->  EXTRA - Dado o id de um artigo apresenta a sua ficha de artigo*/
			viewArtigo(getArtigo(param2));
			write(1,"\n",1);
		break;
		default:
			system("clear");
			catchMessage(MSG_4);
	}
	free(msg);
}