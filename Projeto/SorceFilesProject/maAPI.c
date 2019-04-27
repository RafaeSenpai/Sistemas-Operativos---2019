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
    }
    else{
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


void insereArtigo(char* nome, char* preco){

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
  int l = lseek(fdStr,edr_nome,SEEK_SET);
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

Artigo getArtigo(char* cod){

  int id = atoi(cod);
  int fdArt = open("ARTIGOS.txt", O_RDONLY, 0777);

  ArtigoFile newArtF = malloc(sizeof(struct ArtigoF));
  lseek(fdArt,id*sizeof(struct ArtigoF),SEEK_SET);
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
	free(art);
	return art;
}

/*FAZER UMA FUNÇÃO QUE VERIFICA SE O ARTIGO EXISTE E CASO NAO EXISTA NÃO É
ADICIONADO NENHUM NOME AO FICHEIRO STRINGS NEM ATUALIZADO NENHUM REGISTO NO FICHEIRO ARTIGOS*/

/*
		ULTIMA VERSÃO DA FUNÇÃO DE EDITAR O NOME DO ARTIGO
*/

void editaNome(char* id, char* nome){

  strcat(nome, "\n");

  int fdART = open("ARTIGOS.txt",O_RDWR, 0777);
  int fdSTR = open("STRINGS.txt",O_RDWR, 0777);
  ArtigoFile art = malloc(sizeof(struct ArtigoF));

	int nbSTR = lseek(fdSTR,-1,SEEK_END);
	write(fdSTR, nome,strlen(nome));

	lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
  read(fdART, art, sizeof(struct ArtigoF));
  art->edr_nome = nbSTR;
  lseek(fdART, -sizeof(struct ArtigoF), SEEK_CUR);
	write(fdART, art, sizeof(struct ArtigoF));
	close(fdART);
	close(fdSTR);

	printf("\n\nARTIGO ALTERADO:\n");
	getArtigo(id);
}


/*
void editaNome(char* id, char* nome){

  ArtigoFile art = malloc(sizeof(struct ArtigoF));

  int fdSTR = open("STRINGS.txt", O_RDWR | O_APPEND, 0777);
  strcat(nome, "\n");
  int nbSTR = lseek(fdSTR,0,SEEK_CUR); //nbSTR = 0
  write(fdSTR, nome,strlen(nome));

    // <--------------------- VER DAQUI
  int fdART = open("ARTIGOS.txt",O_RDWR, 0777);
	lseek(fdART, atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
  read(fdART, art, sizeof(struct ArtigoF));
  nbSTR = lseek(fdSTR, -strlen(nome), SEEK_CUR);
  long n = (long)fdART + (long)nbSTR;
  art->edr_nome = (long)&n;
  lseek(fdART, -sizeof(struct ArtigoF), SEEK_CUR);
  write(fdART, art, sizeof(struct ArtigoF));
	close(fdART);
    // <-------------------- ATÉ AQUI
  free(art);

	printf("\n\nARTIGO ALTERADO:\n");
	getArtigo(id);
}
*/

void editaPreco(char* cod, char* preco){

  int fdART = open("ARTIGOS.txt", O_RDWR, 0777);
  lseek(fdART, atoi(cod)*sizeof(struct ArtigoF), SEEK_CUR);
  ArtigoFile art = malloc(sizeof(struct ArtigoF));
  read(fdART, art, sizeof(struct ArtigoF));

  art->preco = atof(preco);

  lseek(fdART, -sizeof(struct ArtigoF), SEEK_CUR);
  printf("id: %d\n", art->id);
  write(fdART, art, sizeof(struct ArtigoF));

  close(fdART);
  free(art);

  printf("\n\nPREÇO ALTERADO\n");
}

//1º abrir o STRINGS
//2º guardar o nome na ultima posição do strings e guardar para um int o nb de bits lidos nesse ficheiro
//3º abrir o ARTIGOS
//4º localizar o artigo com o id passado(getArtigo)
//5º alterar o campo ref_nome desse artigo obtido no passo anterior para o valor de nb obtido no passo 2
