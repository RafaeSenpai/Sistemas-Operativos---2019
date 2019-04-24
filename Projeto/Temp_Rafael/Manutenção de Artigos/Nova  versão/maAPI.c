#include "maAPI.h"


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




ArtigoFile criaStructArtigo(int nbArt, int nbStr, char* name,char* price){
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
	close(fdStr);

int fdArt = open("ARTIGOS.txt", O_CREAT |O_RDWR, 0777);
int nbArt = lseek(fdArt,0,SEEK_END);//devolve o numero lidos até ao final do ficheiro ARTIGOS.txt(nbArt vai dar jeito para inserir o stock em STOCKS.txt)

ArtigoFile newArt = criaStructArtigo(nbArt,nbStr,nome,preco);	

	write(fdArt,newArt,sizeof(struct ArtigoF)); 
	char *id = malloc(sizeof(char) * 30);

	sprintf(id,"%d",newArt->id);

	write(1,id,sizeof(int));
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

	/*
		//Imprimir o conteudo da estrutura generica do artigo
		printf("Conteudo da esrutura de dados 'Artigo':%p\n",art);
		printf("ID: %d\n",art->id);
		printf("Nome: %s\n",art->nome);
		printf("Preço: %f\n",art->preco);
		printf("Stock: %d\n",art->stock);
	*/
	return art;
}