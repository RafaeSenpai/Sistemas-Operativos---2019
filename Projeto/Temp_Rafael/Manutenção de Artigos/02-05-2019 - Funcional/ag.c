#include "ag.h"

/*
	Estrutura de uma Venda no ficheiro Vendas
*/
struct Vendas{
	int idArt;
	float quant;
	float vTotal;
};



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
	    return strcat(nametoAgregationFile,".txt\0");
	
	}else{
	
		catchMessage(ERROR_31);
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
		catchMessage(ERROR_29);
		return NULL;
	}
}





Venda saleToAgregation(int idArt, int numVendas){
int fdVendas = open("VENDAS.txt",O_RDONLY,0777);
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
		catchMessage(ERROR_30);
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
int fdVendas = open("VENDAS.txt",O_RDONLY,0777);
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
			catchMessage(ERROR_32);
		}

	}else{
		catchMessage(ERROR_33);
	}
}



/*
	Imprimir toda a agregação atual
*/
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



/*
	Imprimir toda a agregação no ecra
*/
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