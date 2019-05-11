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


void gerarLogFile(char* nameFileAgg){
	LogFile newLog = malloc(sizeof(struct Log));
printf("VAI CRIAR FICHEIRO AGREGAÇÃO!!\n");
	if(newLog){
		strcpy(newLog->nameFile,nameFileAgg);
		//printf("Nome do ficheri agregado a ser guardado no log(nameFileAgg): %s\n",nameFileAgg);
		//printf("Nome do ficheri agregado a ser guardado no log(newlog->nameFile: %s\n",newLog->nameFile);
		newLog->status = 0;
		//printf("Nome do ficheri agregado a ser guardado no log(newLog->status): %d\n",newLog->status);
		newLog->lastAggregateSale = -1;
		//printf("Nome do ficheri agregado a ser guardado no log(newLog->lastAggregateSale): %d\n",newLog->lastAggregateSale);
		int fdLog = open(LogFileLocal,O_CREAT | O_RDWR,0777);
		if(fdLog){
			lseek(fdLog,0, SEEK_SET);
			write(fdLog, newLog,sizeof(struct Log));
			seeContentLog(fdLog);
			close(fdLog);
			free(newLog);
		}else{
			catchMessage(ERROR_37);
		}

	}else{
		catchMessage(ERROR_36);
	}
}


char* getAggregationFileName(){ //--------------------------------------------------------------------------------OPERACIONAL
	int fdLog = open(LogFileLocal,O_RDONLY,0777);
	if(fdLog){
		char* nomeFicheiro = malloc(50*sizeof(char));
		LogFile data = malloc(sizeof(struct Log));
		if(nomeFicheiro){
			lseek(fdLog,0,SEEK_SET);
			read(fdLog,data,sizeof(struct Log));//<<<<----------pode vir a dar erro aqui!
			close(fdLog);
			return data->nameFile;

		}else{
			catchMessage(ERROR_39);
		}

	}else{
		catchMessage(ERROR_38);
	}
	return NULL;
}


int getLogStatus(){
	int fdLog = open(LogFileLocal,O_RDONLY,0777);
	int status;

	if(fdLog){
		status = -1;
		lseek(fdLog,(-2)*sizeof(int),SEEK_END);
		read(fdLog,&status,sizeof(int));
		close(fdLog);
		return status;
	}else{
		catchMessage(ERROR_40);
	}

	return -1;
}


int getLogLastAggregateSale(){
	int fdLog = open(LogFileLocal,O_RDONLY,0777);
	int lastAggregateSale;

	if(fdLog){
		lastAggregateSale = -1;	
		lseek(fdLog,(-1)*sizeof(int),SEEK_END);
		read(fdLog,&lastAggregateSale,sizeof(int));
		close(fdLog);
		return lastAggregateSale;
	}else{
		catchMessage(ERROR_41);
	}
	return -1;
}


void setLogNewAggregationFileName(char* newName){
	int fdLog = open(LogFileLocal,O_WRONLY,0777);
	if(fdLog){
		LogFile new = malloc(sizeof(struct Log));

			if(new){
				read(fdLog,new,sizeof(struct Log));
				strcpy(new->nameFile,newName);//<<<<----------------------------------------------------pode dar erro aqui!
				printf("new->nameFile : %s\n",new->nameFile);
				printf("newName: %s\n",newName);
				lseek(fdLog,0,SEEK_SET);
				write(fdLog,new,sizeof(struct Log));
				close(fdLog);
				free(new);
			}else{
				close(fdLog);
				catchMessage(ERROR_43);
			}

		}else{
			catchMessage(ERROR_42);
		}
}


void setNewStatus(int newStatus){
	int fdLog = open(LogFileLocal,O_WRONLY,0777);
	if(fdLog){
		lseek(fdLog, (-2)*sizeof(int),SEEK_END);
		write(fdLog,&newStatus,sizeof(int));
		close(fdLog);
	}else{
		catchMessage(ERROR_44);
	}
}





void setLastAggregateSale(int newPosition){
	int fdLog = open(LogFileLocal,O_WRONLY,0777);
	if(fdLog){
		lseek(fdLog,(-1)*sizeof(int),SEEK_END);
		write(fdLog,&newPosition,sizeof(int));
		//seeContentLog(fdLog);//<<<-----------------------------------------------------------------------apagar!!!
		close(fdLog);
	}else{
		catchMessage(ERROR_45);
	}

}


int existLogFile(){
	int fdLog = open(LogFileLocal,O_RDONLY,0777);

	if(fdLog<0){
		close(fdLog);
		return 0;
	}
	return 1;
}

int existSalesFile(){
	int fdVendas = open(SaleFile,O_RDONLY,0777);

	if(fdVendas<0){
		close(fdVendas);
		return 0;
	}
	return 1;
}


float getQuantidade(Venda sale){
	return sale->quant;
}

float getValTotal(Venda sale){
	return sale->vTotal;
}


float getIDArtigo(Venda sale){
	return sale->idArt;
}

int getNumVendas(int fdVendas){ //-------------------------------------------------------------------------------------OPERACIONAL
int totBytes;
	if(fdVendas){
		totBytes = lseek(fdVendas,0,SEEK_END);
		close(fdVendas);
		return totBytes/(sizeof(struct Vendas));
	}else{
		catchMessage(ERROR_46);
	}
	return -1;

}

void viewVendaAggregation(Venda sale){
char* msg = malloc(150*sizeof(char));

	if(sale){

		if(msg){
			sprintf(msg,"\nVenda agregada:\n    ID artigo: %d\n    Quantidade total vendida: %.0f\n    Valor total das vendas: %.2f\n\n",sale->idArt,sale->quant,sale->vTotal);
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

void seeAllAggregation(int fd){
int nAggregSales = getNumVendas(fd);
Venda aux = malloc(sizeof(struct Vendas));
	
	if(aux){
		lseek(fd,0,SEEK_SET);
		for(int i=0; i<nAggregSales; i++){
			lseek(fd, i*sizeof(struct Vendas), SEEK_SET);
			read(fd, aux,sizeof(struct Vendas));
			viewVendaAggregation(aux);
		}
		free(aux);

	}else{
		catchMessage(ERROR_34);
	}
}

Venda getVendaToAggregation(int numVenda){
int fdVendas = open(SaleFile,O_RDONLY);
Venda sale = NULL;

	if(fdVendas){
		int nbEnd = lseek(fdVendas,0,SEEK_END); //numero de bytes existentes ate ao final do ficheiro
		int nbLocal = lseek(fdVendas,numVenda*sizeof(struct Vendas),SEEK_SET);	//numero de bytes até á estrutura que se quer ler
		sale = malloc(sizeof(struct Vendas));
		
		if(sale){

			if(nbLocal<nbEnd){//se o "numero" da venda a procurar não existir retorna NULL
				if(numVenda>=0){	
					lseek(fdVendas,numVenda*sizeof(struct Vendas),SEEK_SET);	
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

int runAggregation(char* aggFileName, int nLastSale){

	int fdAgg = open("aggFileName",O_CREAT | O_RDWR,0777);
	//seeAllAggregation(fdAgg);
	if(fdAgg){
		int fdVendas = open(SaleFile,O_RDONLY,0777);
	
		if(fdVendas){
			Venda sale = malloc(sizeof(struct Vendas));

			if(sale){
					//printf("NOME DO FICHEIRO CORRENTE DE AGREGAÇÃO EM runAggregation(): %s\n\n",aggFileName); //<<<<<---------ESTA LINHA DE CODIGO SERÁ PARA ELIMINAR	
				int nTotalDeVendas = getNumVendas(fdVendas);
				close(fdVendas);

				nLastSale++;//<<<-----para não agregar novamente a ultima venda que tinha sido agregada na ultima agregação
				for(;nLastSale < nTotalDeVendas;nLastSale++){ //<<----pode dar erro aqui por causa do <= ou por causa do for(;...)
printf("\n\n\n\nValor do contador do for nLastSale:%d\n",nLastSale);	
					sale = getVendaToAggregation(nLastSale);
						printf("\n-------NA ESTRUTURA-----------\n");
						printf("Artigo: %d\n",sale->idArt);
						printf("Quantidade: %f\n",sale->quant);
						printf("Total: %f\n",sale->vTotal); 
						printf("--------------------------------\n");
	

					int idArtV = getIDArtigo(sale);
					float qtV = getQuantidade(sale);
					float valTotV = getValTotal(sale);



					lseek(fdAgg,idArtV*sizeof(struct Vendas),SEEK_SET);

					if((read(fdAgg,sale,sizeof(struct Vendas)))==0){//<<---seja já existir uma venda naquela posição ele vai guardar o conteudo dessa venda para a estrutura"sale" e devolver um valor >0, se não existir nenhuma venda naquela posição entao não vai guardar nada para a estrutur sale e vai devolver um valor >0
						write(fdAgg,sale,sizeof(struct Vendas));	




						setLastAggregateSale(nLastSale-1);
						free(sale);
printf("nTotalDeVendas na função runAggregation: %d\n",nTotalDeVendas);
					}else{//<<---caso já exista outra venda do mesmo artigo naquela posição no ficheiro de agregação
printf("Entrou no caso em que encontrou o mesmo artigo na posição!\n");

						sale->quant += qtV;
						sale->vTotal += valTotV;
						write(fdAgg,sale, sizeof(struct Vendas));
						setLastAggregateSale(nLastSale);
						free(sale);
					}
				}
				printf("atualizar status!\n");
				setNewStatus(1);
				return fdAgg;
				
				}else{
					close(fdAgg);
					close(fdVendas);
					catchMessage(ERROR_49);
				}

			}else{
				close(fdAgg);
				catchMessage(ERROR_48);
			}

		}else{
			catchMessage(ERROR_47);
		}

	return -1;
}



void seeContentLog(){
	int fdLog = open(LogFileLocal,O_WRONLY,0777);

	if(fdLog){
		LogFile log = malloc(sizeof(struct Log));
		
		if(log){
			read(fdLog,log,sizeof(struct Log));
			char* msg = malloc(200*sizeof(char));
			printf("Nome do ficheiro no seecontentLog: %s\n",log->nameFile);//<<<<<----------------------------LINHA DE CODIGO PARA REMOVER
			if(msg){
				sprintf(msg,"\nConteudo do ficheiro log:\n    Nome do ultimo ficheiro de agregação criado: %s\n    Posição da ultima venda agregada: %d\n    Valor do status: %d\n\n",log->nameFile,log->status,log->lastAggregateSale);
				write(1,msg,strlen(msg));
				free(msg);
				close(fdLog);
			}else{
				close(fdLog);
				catchMessage(ERROR_52);
			}

		}else{
			close(fdLog);
			catchMessage(ERROR_51);
		}

	}else{
		catchMessage(ERROR_50);
	}
}

void gerarAgregacao(){//<<<--- falta fazer a verificação de se não existir ficheiro de vendas nenhum
	if(existSalesFile()==1){
		if(existLogFile()==1){//<<--caso exista um ficheiro log já criado
			if(getLogStatus()==1){//<<--a ultima agregação foi concluida com sucesso
				setLogNewAggregationFileName(nameFileAggregation());
				setNewStatus(0); //<<---0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
				seeAllAggregation(runAggregation(getAggregationFileName(),getLogLastAggregateSale()));
			}else{//<<--- caso a ultima agregação não tenha sido concluida com sucesso
				
				seeAllAggregation(runAggregation(getAggregationFileName(),getLogLastAggregateSale()));
			}
		}else{//<<---caso não exista nenhum ficheiro log
			gerarLogFile(nameFileAggregation());
				
			seeAllAggregation(runAggregation(getAggregationFileName(),getLogLastAggregateSale()));//<<<<------ O ERRO ESTÁ AQUI!!!!!
		
		}
	}else{
		catchMessage(MSG_10);
	}
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
			seeContentLog();
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