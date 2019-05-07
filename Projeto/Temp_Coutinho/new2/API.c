#include "API.h"

#define ArtgsFile "artigos"
#define SaleFile "vendas"
#define StockFile "stocks"
#define StringFile "strings"

struct ArtigoF
{
  int id;
  int edr_nome;
  float preco;
};

struct Artigo{
	int id;
	char* nome;
	float preco;
	int stock;
};

struct Vendas{
	int idArt;
	float quant;
	float vTotal;
};

char* fileReadLine(int fildes){
  int n;
  char c;
  char* buf = malloc(100 * sizeof(char));
  ssize_t nbytes = 0;

  while((n = read(fildes,&c,1)) > 0 && c != '\n' ){
      buf[nbytes] = c;
      nbytes++;
  }

  return buf;
}

ssize_t readLine(int fildes, void *buf, size_t nbyte){
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

ArtigoFile criaStructArtigo(int nbArt, int nbStr,char* price){//---------------FUNCIONAL
ArtigoFile new = malloc(sizeof(struct ArtigoF));

	if(new){
		new->id = nbArt/sizeof(struct ArtigoF);
		new->edr_nome = nbStr;
		new->preco = atof(price);
		return new;
	}else{
		catchError(ERROR_16);
	}
	return NULL;
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

void insereArtigo(char* nome,char* preco){//-----------------------------------FUNCIONAL
	int fdStr = open("STRINGS.txt", O_CREAT | O_RDWR, 0777);
	int nbStr;

	if(fdStr>-1){
		nbStr = lseek(fdStr,0,SEEK_END);
		write(fdStr,nome,strlen(nome));
		write(fdStr,"\n",sizeof(char));
		close(fdStr);
	}else{
		catchError(ERROR_1);
	}

	int fdArt = open("ARTIGOS.txt", O_CREAT |O_RDWR, 0777);
	if(fdArt>-1){
		int nbArt = lseek(fdArt,0,SEEK_END);

		ArtigoFile newArt = criaStructArtigo(nbArt,nbStr,preco);

		write(fdArt,newArt,sizeof(struct ArtigoF));
    char* msg = malloc(100*sizeof(char));
    sprintf(msg, "ARTIGO INSERIDO: %d\n", newArt->id);
    write(1,msg,strlen(msg));
		char *id = malloc(sizeof(char) * 30);

		if(id){
			sprintf(id,"%d",newArt->id);
			free(id);
		}else{
			catchError(ERROR_18);
		}
		close(fdArt);
		free(newArt);

	}else{
		catchError(ERROR_2);
	}

	int quant = 0;
	int fdStK = open("STOCKS.txt", O_CREAT | O_RDWR | O_APPEND, 0777);

	if(fdStK>-1){
		write(fdStK,&quant,sizeof(int));
		close(fdStK);
	}else{
		catchError(ERROR_3);
	}
}

void atualizaStock(char* cod, char* qt){
  int fdSTK = open("STOCKS.txt", O_RDWR | O_CREAT, 0777);
  printf("fdSTK: %d\n", fdSTK);
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

			if(msg){
				sprintf(msg,"Novo stock: %d\n",newStock);
				write(1,msg,strlen(msg));
				free(msg);

				if(atoi(qt)<0){
					Venda sale = criaStructVenda(cod,qt);
					lseek(fdVendas,sizeof(struct Vendas),SEEK_END);
					write(fdVendas,sale,sizeof(struct Vendas));
					viewVenda(sale);
				}
        close(fdVendas);
        close(fdSTK);
			}
      else{
				catchError(ERROR_12);
			}
      close(fdVendas);
      close(fdSTK);
		}
    else{
			catchError(ERROR_24);
		}
	}
  else{
		catchError(ERROR_9);
	}
  close(fdVendas);
  close(fdSTK);
}

void editaNome(char* id, char* nome){ //-------------------------------FUNCIONAL
int fdSTR = open("STRINGS.txt",O_RDWR);

	if(fdSTR>-1){
		int fdART = open("ARTIGOS.txt",O_RDWR);

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

        write(1,"NOME EDITADO\n",strlen("NOME EDITADO\n"));
			}else{
				write(1,"Não é possivel modificar o nome do artigo com o ID indicado!\n",42);
			}

		}else{
			catchError(ERROR_14);
		}

	}else{
		catchError(ERROR_7);
	}
}

void editaPreco(char* idC, char* precoC){//--------------------------FUNCIONAL

  float preco;
  int id = atoi(idC);
  int fdART = open("ARTIGOS.txt", O_RDONLY | O_WRONLY | O_CREAT);

  printf("here\n%d\nhere\n", fdART);

	if(fdART>-1){
		int nbEnd = lseek(fdART,0,SEEK_END);
		int nbLocal = lseek(fdART,id*sizeof(struct ArtigoF),SEEK_SET);

		if(nbLocal<nbEnd){
			lseek(fdART,id*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
			preco = atof(precoC);
			write(fdART, &preco, sizeof(float));
      write(1,"PREÇO EDITADO\n",strlen("PREÇO EDITADO\n"));
      close(fdART);
		}else{
			write(1,"Não é possivel modificar o preço do artigo com o ID indicado!\n",66);
			close(fdART);
		}
	}else{
		catchError(ERROR_8);
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

Artigo getArtigo(char* id){ //--------------------FUNCIONAL!!!-------APENAS FAZER COM QUE DADO UM ID DE UM ARTIGO que nao existe ESTE NÃO APRESENTE INFORMAÇÃO NENHUMA
int fdArt = open("ARTIGOS.txt", O_RDONLY, 0777);

	if(fdArt>-1){
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
					art->stock = getStockI(newArtF->id);
					free(newArtF);
					close(fdArt);
					/*
						Não posso fazer free do malloc (art) desta função porque snão perco a informação que quero
						retornar, mas em contra partida quando faço get de uma artigo que nao existe este devolve-me
						parte da informação relativa a um artigo existente
					*/
					return art;

				}else{
					catchError(ERROR_23);
				}

			}else{
				catchError(ERROR_21);
			}

		}else{
			return NULL;
		}

	}else{
		catchError(ERROR_6);
	}

	return NULL;
}

char* getNome(int edr_nome){//----------------------------------------------FUNCIONAL
int fdStr = open("STRINGS.txt", O_RDONLY, 0777);
	if(fdStr>-1){
		char* nome = malloc(100*sizeof(char));
		if(nome){
			lseek(fdStr,edr_nome,SEEK_SET);
			readLine(fdStr,nome,100); //se colocar no lugar do 100, strlen(nome) o nome do artigo deixa de aparecer
			close(fdStr);
			//Não posso fazer free do malloc desta função porque não perco a informação que quero retornar
			return nome;
		}else{
			catchError(ERROR_19);
		}
	}else{
		catchError(ERROR_4);
	}
	return NULL;
}

int getStockC(char* id){ //-------------------------------------------------------FUNCIONAL
  int fdStK = open("STOCKS.txt", O_RDONLY, 0777);
  int stk;

	if(fdStK){
		lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
		read(fdStK,&stk,sizeof(int));
		close(fdStK);
		return stk;
	}else{
		catchError(ERROR_10);
	}
  close(fdStK);
	return 0;
}

int getStockI(int id){
int fdStK = open("STOCKS.txt", O_RDONLY, 0777);

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
			catchError(MSG_5);
		}

	}else{
		catchError(ERROR_5);
	}

return 0;
}

float getPreco(char* id){

  int fdART = open("ARTIGOS.txt",O_RDWR, 0777);
  float preco = 0.0;

	if(fdART){
		lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
		read(fdART,&preco,sizeof(float));
		close(fdART);
		return preco;
	}else{
		catchError(ERROR_11);
	}
	return 0;
}

void getStockAndPrice(char* id){ //---------------------------------------------FUNCIONAL

  char* msg = malloc(100 * sizeof(char));

	sprintf(msg,"Stock: %d\nPreço: %.2f\n\n", getStockC(id), getPreco(id));
	write(1,msg,strlen(msg));
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
			catchError(ERROR_20);
		}

	}else{
		write(1,"Artigo inexistente!\n",21);
	}
}

int getNumVendas(int fd){
  int totBytes = lseek(fd,0,SEEK_END);//Numero de bytes lidos até á inserção do artigo no ficheiro artigos

	return totBytes/(sizeof(struct Vendas));
}

char* nameFileAgregation(){
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

		catchError(ERROR_31);
		return NULL;
	}
}

Venda agCriaStructVenda(int idArtigo, float qtdTotalVendas, float totalVendas){
  Venda new = malloc(sizeof(struct Vendas));

	if(new){
		new->idArt = idArtigo;
		new->quant = qtdTotalVendas;
		new->vTotal = totalVendas;
		return new;
	} else{
		catchError(ERROR_29);
		return NULL;
	}
}

Venda saleToAgregation(int idArt, int numVendas){
  int fdVendas = open(SaleFile,O_RDONLY,0777);
  float quantidade;
  float somaTodasQuantidades=0;
  float totalVenda;
  float somaTodosTotaisV=0;
  int id;

	if(fdVendas){
		for(int i=0; i<numVendas; i++){
			lseek(fdVendas, i*sizeof(struct Vendas), SEEK_SET);
			read(fdVendas, &id, sizeof(int));

			if(id==idArt){
				lseek(fdVendas, (i*sizeof(struct Vendas)) + sizeof(int), SEEK_SET);
				read(fdVendas, &quantidade, sizeof(float));
				somaTodasQuantidades += quantidade;

				lseek(fdVendas, (i*sizeof(struct Vendas)) + sizeof(int) + sizeof(float), SEEK_SET);
				read(fdVendas, &totalVenda, sizeof(float));
				somaTodosTotaisV += totalVenda;
			}
		}
		close(fdVendas);
		return agCriaStructVenda(idArt,somaTodasQuantidades,somaTodosTotaisV);
	}else{
		catchError(ERROR_30);
		return NULL;
	}

}

int existArtInAggregation(int fd, int id, int numArtig){
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

void geraAgregacao(){
int aggregationFile = open(nameFileAgregation(),O_CREAT | O_RDWR | O_APPEND, 0777); //<<--- é criado o ficheiro de agregação com o nome igual á data do momento em que é gerada a agregação
int fdVendas = open(SaleFile,O_RDONLY,0777);
int nSales = getNumVendas(fdVendas);//<<---- numero de vendas existente no ficheiro VENDAS.txt
int idArt;

	if(aggregationFile){

		if(fdVendas){

			for(int i = 0; i<nSales; i++){
				lseek(fdVendas, i*sizeof(struct Vendas), SEEK_SET);
				read(fdVendas, &idArt, sizeof(int));//<<----- lê apenas o campo referente ao id para a variavel idArt

				if(existArtInAggregation(aggregationFile,idArt,nSales) != 1){
					lseek(aggregationFile,0,SEEK_END); //<<<----------------------------------------------não sei até que ponto é necessário ter este LSEEK tendo em conta que o descritor é aberto de forma a que as escritas sejam feitas no final do ficheiro
					write(aggregationFile, saleToAgregation(idArt, nSales),sizeof(struct Vendas));
				}
			}
//			close(aggregationFile); //<---- supostamente nao é necessário ter este close do descritor pois como logo a seguir é chamada a função de impressão da agregação, esta mesma função de impressao trata de fechar o descritor
			seeAllAggregation(aggregationFile);
			close(fdVendas);

		}else{
			catchError(ERROR_32);
		}

	}else{
		catchError(ERROR_33);
	}
}

void viewVendaAggregation(Venda sale){
char* msg = malloc(150*sizeof(char));

	if(sale){

		if(msg){
			sprintf(msg,"\nVenda agregada:\n    ID artigo: %d\n    Quantidade total vendida: %.0f\n    Valor total das vendas: %.2f\n\n",sale->idArt,sale->quant,sale->vTotal);
			write(1,msg,strlen(msg));
			free(msg);
		}else{
			catchError(ERROR_28);
		}

	}else{
		free(sale);
		catchError(MSG_3);
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
		catchError(ERROR_34);
	}
}

void menuComandosCV(char* buffer){//----------------------------------------------FUNCIONAL
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
			catchError(MSG_4);
	}
}

void menuComandosMA(char* buffer){//-------------------------------------FUNCIONAL
  char* param1 = strtok(buffer," ");
  char* param2 = strtok(NULL," ");
  char* param3 = strtok(NULL," ");
  char* msg = malloc(50*sizeof(char));
  char* line = malloc(100*sizeof(char));

  int fd, n;

	switch(*param1){
		case 'i':
			insereArtigo(param2,param3);
			break;
		case 'n':
			/*n <código> <novo nome> --> altera nome do artigo*/
			editaNome(param2,param3);
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
			sprintf(msg, "Stock do artigo: %d é de %d unidades\n",atoi(param2),getStockI(atoi(param2)));
			write(1, msg,48);
      break;
		default:
			system("clear");
			write(1,"Opção inválida!\nInsira novo comando:\n",41);
	}
	free(msg);
}
