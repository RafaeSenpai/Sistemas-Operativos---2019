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



//-----------------API AGREGADOR -------------------
char* nameFileAgregation(){//---------------------------------------------------------------------------------------SUPOSTAMENTE OPERACIONAL
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



/*
	Devolve o numero de vendas desde uma determinada posição do ficheio VENDAS, indicada pelo 
	inteiro existente no inicio do ficheiro VENDAS, que representa o numero da ultima 
	venda incluida da ultima agregação até á ultima venda registada no ficheiro VENDAS.
	É feita a contabilização de todos os bytes referentes 
	ao fichiro vendas, em seguida é subtraido a esse mesmo numero de bytes os bytes reservados 
	ao inteiro que indica qual foi a ultima venda incluida na ultima agregação e desta forma 
	temos o numero total de bytes do ficheiro VENDAS referentes somente a vendas(estruturas de vendas).
	Ao resultado obtido até ao momento é então subtraido os bytes contidos no ficheiro desde a ultima 
	venda agregada até a ultima venda registada.
	Por fim, a ultimo resultado, é feita a divisão pelo tamanho da estrutura de uma venda e desta forma 
	obtem-se o numero de vendas efetuadas desde a ultima agregação.
*/
int getNumVendas(int fd,int posInicial){//........------------------------------------------------------------------SUPOSTAMENTE OPERACIONAL

		int totBytes = (lseek(fd,0,SEEK_END) - sizeof(int)) - lseek(fd,posInicial*sizeof(struct Vendas),SEEK_SET);//Numero de bytes lidos até á inserção do artigo no ficheiro artigos
	
	return totBytes/(sizeof(struct Vendas));//a subtração do sizeof(int) advem que para calcular o numero de vendas no ficheiro, o inteiro que é guardado no inicio do ficheiro(referente ao nº da ultima linha que foi agregada na ultima agregação) vendas não deve ser tido em conta para o calculo
}





Venda agCriaStructVenda(int idArtigo, float qtdTotalVendas, float totalVendas){ //----------------------------------SUPOSTAMENTE  OPERACIONAL
Venda new = malloc(sizeof(struct Vendas));

	if(new){
		new->idArt = idArtigo;
		new->quant = qtdTotalVendas;
		new->vTotal = totalVendas;
		return new;
	} else{
		catchMessage(ERROR_29);
		return NULL;
	}
}





Venda saleToAgregation(int idArt, int lastSaleInclAggr, int numVendas){ //----------------------ULTIMO PASSO! ------>SUPOSTAMENTE OPERACIONAL<-------
int fdVendas = open(SaleFile,O_RDONLY,0777);
float quantidade;
float somaTodasQuantidades=0;
float totalVenda;
float somaTodosTotaisV=0;
int id;
	
	if(fdVendas){
		lseek(fdVendas,sizeof(int) + lastSaleInclAggr*sizeof(struct Vendas),SEEK_SET); //<<-----posiciona-se no ficheiro VENDAS para o local onde deve começar a fazer a agregação não esquecendo que tem que somar o espaºo reservado do inteiro no inicio do ficheiro
		for(int i=0; i<numVendas; i++){
			lseek(fdVendas, i*sizeof(struct Vendas), SEEK_CUR);//<<---------------começa a agregar os dados a partir do ponto determinado no passo anterior
			read(fdVendas, &id, sizeof(int));//<<---------------------------------captura o id do artigo na posição corrente no ficheiro VENDAS

			if(id==idArt){//<<----------------------------------------------------verifica se o id capturado no passo anterior é igual ao id do artigo(idArt) que se quer encontrar
				lseek(fdVendas, sizeof(int) + (i*sizeof(struct Vendas)) + sizeof(int), SEEK_SET); //<<-------verificada a igualdade no paso anterior reposiciona-se no ficheiro para a leitura e armazenamento da venda no ficheiro VENDAS para as devidas variaveis
				read(fdVendas, &quantidade, sizeof(float));
				somaTodasQuantidades += quantidade; //<<-----------------------------------------------------vai acumulando a soma de todos as informações, neste caso, todas as quantidades vendidas
				
				lseek(fdVendas, sizeof(int) + (i*sizeof(struct Vendas)) + sizeof(int) + sizeof(float), SEEK_SET);//<<------repete os ultimos 3 passos anteriores, mas agora para os totais das vendas
				read(fdVendas, &totalVenda, sizeof(float));
				somaTodosTotaisV += totalVenda;
			}
		}
		close(fdVendas);
		return agCriaStructVenda(idArt,somaTodasQuantidades,somaTodosTotaisV);//<<------guarda as somas dos resultados numa estrutura do tipo venda e armazena a mesma no ficheiro de agregação
	}else{
		catchMessage(ERROR_30);
		return NULL;
	}

}





int existArtInAggregation(int fd, int id, int numArtig){//-----------------------------------------------------------SUPOSTAMENTE OPERACIONAL
int currentID;

	for(int i=0; i<=numArtig; i++){
		lseek(fd,i*sizeof(struct Vendas),SEEK_SET);
		read(fd,&currentID,sizeof(int));
		if(currentID==id){
			return 1;
		}
	}
	return 0;
}






void geraAgregacao(){//----------------------------------------------------------------------------------------------SUPOSTAMENTE OPERACIONAL
int aggregationFile = open(nameFileAgregation(),O_CREAT | O_RDWR | O_APPEND, 0777); //<<--- é criado o ficheiro de agregação com o nome igual á data do momento em que é gerada a agregação
int fdVendas = open(SaleFile,O_RDONLY,0777);



	if(aggregationFile){	

		if(fdVendas){
			lseek(fdVendas,0,SEEK_SET);
			int ultLinhaAgregada;
			read(fdVendas,&ultLinhaAgregada,sizeof(int));//------captura o valor referente ao numero da ultima venda incluida na ultima agregação
			int nSales = getNumVendas(fdVendas,ultLinhaAgregada);//<<---- numero de vendas existente no ficheiro VENDAS desde a ultima agregação até ao momento
			int idArt;			
			int lastSaleInclAggr = ultLinhaAgregada;

			for(;ultLinhaAgregada<nSales; ultLinhaAgregada++){
				lseek(fdVendas, ultLinhaAgregada*sizeof(struct Vendas), SEEK_SET);
				read(fdVendas, &idArt, sizeof(int));//<<----- lê apenas o campo referente ao id para a variavel idArt
				
				if(existArtInAggregation(aggregationFile,idArt,nSales) != 1){
					lseek(aggregationFile,0,SEEK_END); //<<<----------------------------------------------não sei até que ponto é necessário ter este LSEEK tendo em conta que o descritor é aberto de forma a que as escritas sejam feitas no final do ficheiro
					write(aggregationFile, saleToAgregation(idArt, lastSaleInclAggr, nSales),sizeof(struct Vendas));
				}
			}
//			close(aggregationFile); //<---- supostamente nao é necessário ter este close do descritor pois como logo a seguir é chamada a função de impressão da agregação, esta mesma função de impressao trata de fechar o descritor
			seeAllAggregation(aggregationFile);
			close(fdVendas);

		}else{
			catchMessage(ERROR_32);
		}

	}else{
		catchMessage(ERROR_33);
	}
}



/*
	Imprimir toda a agregação atual
*/
void viewVendaAggregation(Venda sale){//----------------------------------------------------------------------------SUPOSTAMENTE OPERACIONAL
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



/*
	Imprimir toda a agregação no ecra
*/
void seeAllAggregation(int fd){ //----------------------------------------------------------------------------------SUPOSTAMENTE OPERACIONAL
int nAggregSales = getNumVendas(fd,0);
Venda aux = malloc(sizeof(struct Vendas));
	
	if(aux){
		lseek(fd,0,SEEK_SET);
		for(int i=0; i<nAggregSales; i++){
			lseek(fd, sizeof(int) + (i*sizeof(struct Vendas)), SEEK_SET);
			read(fd, aux,sizeof(struct Vendas));
			viewVendaAggregation(aux);
		}
		free(aux);
	}else{
		catchMessage(ERROR_34);
	}
}
//----------------FIM API AGREGADOR -----------------------






//----------------API Cliente de Vendas -------------------
Venda criaStructVenda(char* idArt, char* quant){//--------------------------------OPERACIONAL
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


void atualizaStock(char* cod, char* qt){//<<----------------------------------------SUPOSTAMENTE FUNCIONAL
int fdSTK = open(StockFile,O_RDWR);
int qtdAtual = 0;
int newStock = 0;


	if(fdSTK>-1){
		int nbLocal = lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
		int nbEnd = lseek(fdSTK,0,SEEK_END);
		
		if(nbLocal<nbEnd){
			int fdVendas = open(SaleFile,O_CREAT | O_RDWR | O_APPEND,0777);
			
			if(fdVendas>-1){
				lseek(fdSTK, sizeof(int) + (atoi(cod)*sizeof(int)),SEEK_SET); //<-------------------O sizeof(int) no inicio da descrição offset é referente ao inteiro guardado no inicio do ficheiro, este inteiro indica o numero da ultima linha que foi agregada
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





Venda getVenda(char* x){ //----------------------------SUPOSTAMENTE FUNCIONAL
int fdVendas = open(SaleFile,O_RDONLY);
Venda sale = NULL;

	if(fdVendas){
		int nbEnd = lseek(fdVendas,0,SEEK_END); //numero de bytes existentes ate ao final do ficheiro
		int nbLocal = lseek(fdVendas,sizeof(int) + (atoi(x)*sizeof(struct Vendas)),SEEK_SET);	//numero de bytes até á estrutura que se quer ler; O sizeof(int) no inicio da descrição offset é referente ao inteiro guardado no inicio do ficheiro, este inteiro indica o numero da ultima linha que foi agregada
		sale = malloc(sizeof(struct Vendas));
		
		if(sale){

			if(nbLocal<nbEnd){//se o "numero" da venda a procurar não existir retorna NULL
				if(atoi(x)>=0){	
					lseek(fdVendas,sizeof(int) + (atoi(x)*sizeof(struct Vendas)),SEEK_SET);	
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

void menuComandos(char* buffer){
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
int countParams = 0;
char* x = "gv";
char* ag = "ag";
	
	while(countParams==0){	

		if(strcmp(param1,x) == 0){
			countParams = 4;
		}else if(strcmp(param1,ag) == 0){
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
			geraAgregacao();
			break;
		case 4:
			/*EXTRA - FUnção usada para confirmar se os dados são corretamente guardados*/
			viewVenda(getVenda(param2));
			write(1,"\n\n",2);
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
		case 's':	
			/*s <codigo>  -->  EXTRA - Dado um id de artigo devolve o seu stock*/
			sprintf(msg, "Stock do artigo: %d é de %d unidades\n",atoi(param2),getStock(atoi(param2)));
			write(1, msg,48);	
		break;
		default:
			system("clear");
			catchMessage(MSG_4);
	}
	free(msg);
}