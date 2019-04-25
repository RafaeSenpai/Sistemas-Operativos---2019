#include "maAPI.h"
#include <stdlib.h>

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



int verifDescrt(int descArtig, int descStr){

	if(descArtig <0){
		write(2, "Erro na gravação do artigo no ficheiro ARTIGOS.txt!\n", 51);
		exit(0);
	}else if (descStr <0){
		write(2, "Erro na gravação do nome do artigo no ficheiro STRINGS.txt!\n", 61);
		exit(0);
	}
	return 0;
}




ArtigoFile criaStructArtigo(int nbArt, int nbStr,char* price){
ArtigoFile new = malloc(sizeof(struct ArtigoF));
	
	new->id = nbArt/sizeof(struct ArtigoF); //new->id fica com o resultado do nº de bytes lidos até ao final do ficheiro ARTIGOS.txt dividido pelo tamanho da struct que define um artigo
	new->edr_nome = nbStr;//new->id fica com o nº de bytes lidos até ao final do ficheiro STRINGS
	new->preco = atof(price);

return new;
}



Stock criaStructStock(int nbArt,int quantidade){
	Stock newStk = malloc(sizeof(struct Stock));

	newStk->id_Artg = nbArt;
	newStk->stock = quantidade;

return newStk;
}


void insereArtigo(char* nome,char* preco){
int fdStr = open("STRINGS.txt", O_CREAT |O_RDWR, 0777);

/*
	nb: numero de bytes lidos até ao final do ficheiro STRINGS.txt
	lseek: vai colocar o apontador para o final do ficheiro
*/
int nbStr = lseek(fdStr,0,SEEK_END); 
	write(fdStr,nome,strlen(nome));
	write(fdStr,"\n",sizeof(char));
	close(fdStr);

int fdArt = open("ARTIGOS.txt", O_CREAT |O_RDWR, 0777);
int nbArt = lseek(fdArt,0,SEEK_END);//devolve o numero lidos até ao final do ficheiro ARTIGOS.txt(nbArt vai dar jeito para inserir o stock em STOCKS.txt)

ArtigoFile newArt = criaStructArtigo(nbArt,nbStr,preco);	

	write(fdArt,newArt,sizeof(struct ArtigoF)); 
	char *id = malloc(sizeof(char) * 30);

	sprintf(id,"%d",newArt->id);

	write(1,id,sizeof(int));//<---provavelmente dará problemas aquando houver IDs com mais que 4 caracteres
	close(fdArt);


int fdStK = open("STOCKS.txt", O_CREAT | O_RDWR, 0777);
lseek(fdStK,0,SEEK_END);

Stock newStk = criaStructStock(nbArt,0);
	write(fdStK,newStk,sizeof(struct Stock));
	close(fdStK);

	free(id);
	free(newArt);
	free(newStk);
}


char* getNome(int edr_nome){
int fdStr = open("STRINGS.txt", O_RDONLY, 0777);
char* nome = malloc(50*sizeof(char));
	/**/
	lseek(fdStr,edr_nome,SEEK_SET);
	readln(fdStr,nome,50);

	return nome;
}


int getStock(int id){
int fdStK = open("STOCKS.txt", O_RDONLY, 0777);
Stock stk = malloc(sizeof(struct Stock));

	lseek(fdStK,id*sizeof(struct Stock),SEEK_SET);
	read(fdStK,stk,sizeof(struct Stock));

	return stk->stock;
}


Artigo getArtigo(char* id){
int fdArt = open("ARTIGOS.txt", O_RDONLY, 0777);

	lseek(fdArt,(atoi(id))*sizeof(struct ArtigoF),SEEK_SET); 
	ArtigoFile newArtF = malloc(sizeof(struct ArtigoF));
	read(fdArt,newArtF,sizeof(struct ArtigoF));

	Artigo art = malloc(sizeof(struct Artigo));

	art->id = newArtF->id;
	art->nome = getNome(newArtF->edr_nome);
	art->preco = newArtF->preco;
	art->stock = getStock(newArtF->id);
	
		//Imprimir o conteudo da estrutura generica do artigo
		printf("----------------FICHA DE ARTIGO-------------\n");
		printf("Conteudo da esrutura de dados 'Artigo':%p\n",art);
		printf("ID: %d\n",art->id);
		printf("Nome: %s\n",art->nome);
		printf("Preço: %f\n",art->preco);
		printf("Stock: %d\n",art->stock);

	free(newArtF);	
	close(fdArt);
	free(art);//<-------sem isto, quando fazemos procurar alguns artigos e na ultima procura fazemos a procura de um artigo que nao existe, os dados que são apresentados sao os dados do ultimo artigo existente que foi devolvido 
	return art;
}



/*FAZER UMA FUNÇÃO QUE VERIFICA SE O ARTIGO EXISTE E CASO NAO EXISTA NÃO É 
ADICIONADO NENHUM NOME AO FICHEIRO STRINGS NEM ATUALIZADO NENHUM REGISTO NO FICHEIRO ARTIGOS*/



/*
		ULTIMA VERSÃO DA FUNÇÃO DE EDITAR O NOME DO ARTIGO
*/
void editaNome(char* id, char* nome){
int fdART = open("ARTIGOS.txt",O_RDWR);
int fdSTR = open("STRINGS.txt",O_RDWR | O_APPEND);


	strcat(nome, "\n");

	int nbSTR = lseek(fdSTR,0,SEEK_CUR);
	write(fdSTR, nome,strlen(nome));
	

	lseek(fdART,atoi(id)*sizeof(struct ArtigoF)+sizeof(int),SEEK_SET);
	write(fdART, &nbSTR, sizeof(int));
	close(fdART);
	close(fdSTR);

	printf("\n\nARTIGO ALTERADO:\n");
	getArtigo(id);
}








/*
void editaNome(char* id, char* nome){
int fdStr = open("STRINGS.txt", O_RDWR | O_APPEND, 0777);

	write(fdStr,nome,strlen(nome));
	write(fdStr,"\n",sizeof(char));
//int nbStr = lseek(fdStr,0,SEEK_END);    
printf("ID = %d   |   Nome = %s\n",atoi(id),nome);

int fdArt = open("ARTIGOS.txt,", O_RDWR, 0777);
ArtigoFile tmp = malloc(sizeof(struct ArtigoF));
	//lseek(fdArt,atoi(id)*sizeof(struct ArtigoF) + sizeof(int),SEEK_SET);
	//write(fdArt,&nbStr,sizeof(int));
	l//seek(fdArt, (-2)*sizeof(int),SEEK_CUR);
	//read(fdArt,tmp,sizeof(struct ArtigoF));
	
	lseek(fdArt,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
	//read(fdArt,tmp,sizeof(struct ArtigoF));


		//Imprimir o conteudo da estrutura generica do artigo
		printf("\n\n\n----------------------Antes da lteração do nome-------------------------------\n");	
		printf("Conteudo da esrutura de dados 'Artigo' tmp:%p\n",tmp);
		printf("ID: %d\n",tmp->id);
		printf("Nome: %d\n",tmp->edr_nome);
		printf("Preço: %.2f\n",tmp->preco);

	
		lseek(fdArt,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
		write(fdArt,&tmp->id,sizeof(int));
		
		int nbStr = lseek(fdStr,(-1)*(strlen(nome)+1),SEEK_END);
		tmp->edr_nome = nbStr;

		lseek(fdArt,atoi(id)*sizeof(struct ArtigoF)+sizeof(int)+sizeof(int),SEEK_SET);
		write(fdArt,&tmp->preco,sizeof(float));

	
	  
	
		//Imprimir o conteudo da estrutura generica do artigo
		printf("----------------------Resultado final da alteração do nome---------------------\n");	
		printf("Conteudo da esrutura de dados 'Artigo' tmp:%p\n",tmp);
		printf("ID: %d\n",tmp->id);
		printf("Nome: %d\n",tmp->edr_nome);
		printf("Preço: %.2f\n",tmp->preco);
	free(tmp);
	close(fdStr);
	close(fdArt);



//1º abrir o STRINGS
//2º guardar o nome na ultima posição do strings e guardar para um int o nb de bits lidos nesse ficheiro
//3º abrir o ARTIGOS
//4º localizar o artigo com o id passado(getArtigo)
//5º alterar o campo ref_nome desse artigo obtido no passo anterior para o valor de nb obtido no passo 2
}
*/