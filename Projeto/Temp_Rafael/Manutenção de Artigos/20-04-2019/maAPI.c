#include "maAPI.h"
#include "maPARSERS.h"
#include <unistd.h>
#include <fcntl.h>


/*
	Verifica integridade dos descritores dos ficheiros e caso algum deles falhe 
	é devolvido um inteiro que identifica o respetivo descritor, porporcionando 
	desta forma a identificação do descritor que falhou!
	
	NOTA: Devolve 0 no caso de estar tudo conforme com os descritores

		exit(0) - indicates successful program termination & it is fully portable, While
		exit(1) - (usually) indicates unsucessful termination. However, it's usage is non-portable.
*/
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




/*
	COnta o numero de nome de artigos no ficheiro Artigos
*/
int numLines(char *file){
int numLinhas = 0;
char c;
FILE *ficheiro;

	ficheiro = fopen(file,"r");

	if(ficheiro!=NULL){
		while(c!=EOF){
			c = fgetc(ficheiro);
			if(c == '\n'){
				numLinhas++;
			}
		}
		fclose(ficheiro);
	}
return numLinhas;
}



ssize_t readln(int fildes, void *buf, size_t nbyte){
ssize_t nbytes = 0;
int n;
char c;
char *buffer = (char *)buf;

    
    while( nbytes < nbyte && (n = read(fildes,&c,1)) > 0 && c != '\n' )
        buffer[nbytes++] = c;
    
    (nbytes < nbyte) ? (buffer[nbytes] = '\0') : (buffer[nbytes-- - 1] = '\0');
    
    return nbytes;
}




NomeArtigo structNomeArtigo(char* name){
NomeArtigo new;

	new = malloc(sizeof(NomeArtigo));
	strcpy(new->nome, name);
	new->dim = strlen(name);

return new;
}

/*
	Estrutura de Artigo a ser guardada no ficheiro ARTIGOS.txt
*/
ArtigoFile structArtigoFile(int *fileART, int *fileSTR, char* name,char* price){
ArtigoFile new;
int bt1 = lseek(*fileSTR,0,SEEK_END);//devolve o numero lidos até ao final do ficheiro STRINGS.txt
int bt2 = lseek(*fileART,0,SEEK_END);//devolve o numero lidos até ao final do ficheiro ARTIGOS.txt

new = malloc(sizeof(struct ArtigoF));
	
	new->id = bt2/sizeof(struct ArtigoF); //new->id fica com o resultado do nº de bytes lidos até ao final do ficheiro ARTIGOS.txt dividido pelo tamanho da struct que define um artigo
	new->ind_nome = bt1/sizeof(struct NomeArtigo); //new->id fica com o nº de bytes lidos até ao final do ficheiro STRINGS
	new->preco = atof(price);

return new;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char* getNome(int ref_nome){

char nome[128];

	int fileSTRS = open("STRINGS.txt", O_RDONLY, 0777);

	if (fileSTRS<0){
		write(2, "Erro na gravação do artigo no ficheiro STRINGS.txt!\n", 51);
		exit(0);
	}else{
		lseek(fileSTRS,ref_nome*sizeof(NomeArtigo),SEEK_SET);
		read(fileSTRS,nome,1);
		close(fileSTRS);
		write(1,nome,sizeof(nome));
	}

	printf("Nome do artigo dentro da função: %s\n",nome);
return nome;
}


/*
	Atraves do ficheiro ARTIGOS.txt, obter o artigo pelo seu ID

	OBS: O id é igual ao numero da linha em que se encontra o nome do artigo 
	no ficheiro STRINGS.txt

	NOTA: Obter o artigo pelo seu id, significa que a função irá retornar uma
	posição no ficheiro ARTIGOS.txt que indica o inicio dos bytes que formam a 
	estrutura de dados de um artigo. Quando se quiser aceder ás devidas caracteristicas 
	do artigo, esse mesmo acesso será feito como numa simples estrutura de dados 
*/

ArtigoFile getArtigo(char* id){ //----------------------.------------------PERCEBER PORQUE QUE NÃO DEVOLVE O QUE QUERO!
ArtigoFile art = malloc(sizeof(struct ArtigoF));

	int fileARTGS = open("ARTIGOS.txt", O_RDONLY, 0777);

	if (fileARTGS<0){
		write(2, "Erro na gravação do artigo no ficheiro ARTIGOS.txt!\n", 51);
		exit(0);
	}else{
		lseek(fileARTGS,(-1)*atoi(id)*sizeof(art),SEEK_END);

		read(fileARTGS,art,atoi(id)*sizeof(art));

		write(1,art,4);
	}
	close(fileARTGS);



	printf("ID do art: %d\n",art->id);
	printf("REF_NOME do art: %c\n",getNome(art->ind_nome));
	printf("PRECO do art: %c\n",art->preco);
	return art->id;
}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------------------------------------SO CONFIGO CONFIRMAR QUE FUNCIONA QUANDO O getArtigo


/*
	Dado o nome e o preço de artigo, é adicionada a informação do mesmo e 
	gerado o respetivo ID do produto no ficheiro ARTIGOS.txt e a string 
	correspondente ao nome do artigo é adicionada ao final do ficheiro STRINGS.txt 
*/
void insereArtigo(char* nome,char* preco){
ArtigoFile art;
NomeArtigo artName;

char codArtigo[30];
int fileARTGS = open("ARTIGOS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
int fileSTRS = open("STRINGS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);

art = structArtigoFile(&fileARTGS,&fileSTRS,nome,preco);
artName = structNomeArtigo(nome);

	if(verifDescrt(fileARTGS,fileSTRS) == 0){

		write(fileSTRS,artName,sizeof(artName));
		/*
			Quando é para escrever no ficheiro artigos um artigo (<id> <ref nome> <preco>) 
			que é gravado é uma struct que contem os tres campos, id, ref nome e o preço.
		*/
		write(fileARTGS,art,sizeof(art));
	}else{
		verifDescrt(fileARTGS,fileSTRS);
		exit(0);
	}
	close (fileARTGS);
	close (fileSTRS);

	sprintf(codArtigo, "%d", art->id); // converte o id(float) da estrutura e converte e string
	printf("Cod: Artigo: %d\n",art->id);
	write(1,codArtigo,strlen(codArtigo)); // escreve no ecra o codigo do artigo


}





void callCommands(char* buffer){
char inst = takeInstBuff(buffer);
	//colocar aqui uma função que identifica a instrução, o nome de artigo e o preço do mesmo
	switch(inst){
		case 'i':
			insereArtigo( takeNomeBuff(buffer), takePrecoBuff(buffer)); 
			/*funcção que lê do buffer os restantes parametros guardados no buffer e aplica-os 
			á função de inserção:  i <nome> <preço>  --> insere novo artigo, mostra o código */
			break;
		case 'n':
			/*n <código> <novo nome> --> altera nome do artigo*/
			break;
		case 'p':
			/*p <código> <novo preço>   --> altera preço do artigo*/
			break;
		case 't':	
			getArtigo(takeIDBuff(buffer));
		break;
		default:
			printf("Opção inválida!\n");
	}

}










































/*
	Dado um id seguido do novo nome, altera o nome do artigo com o id enviado

	OBS: O novo nome é adicionado no final do ficheiro STRINGS.txt enquanto 
		 que no ficheiro ARTIGOS.txt é feita a procura do artigo e atualizada a
		 referencia do seu nome

	PROTOTIPO:		n <código> <novo nome>
*/
void editName(char* id, char* nome){

}



/*
	Dado o id do artigo e um preço efetua a alteração do preço do artigo. Tal alteração 
	só tem implicações no ficheiro ARTIGOS.txt

	PROTOTIPO:		p <código> <novo preço>
*/
void editPrice(char* idArtigo, char* preco){

}



/*
	Dado o descritor de ficheiro e um id do artigo vai buscar ao ficheiro 
	STOCKS.txt o stock de um artigo

	NOTA: O valor devolvido já será um float, que é do mesmo tipo de 
		  retorno do getPrice(,), pois é conveniente que os tipos sejam os 
		  mesmos para que nao haja problemas de tipos quando se aplicar operações 
		  aritmeticas no mesmos valores correspondentes
*/
float getStock(int *ficheiro,int idArtigo){

return 0;
}


/*
	Dado o descritor de ficheiro e um id do artigo vai buscar ao ficheiro 
	ARTIGOS.txt o seu preço

	NOTA: O valor devolvido já será um float, que é do mesmo tipo de 
		  retorno do getPrice(,), pois é conveniente que os tipos sejam os 
		  mesmos para que nao haja problemas de tipos quando se aplicar operações 
		  aritmeticas no mesmos valores correspondentes
*/
float getPrice(int *ficheiro, int idArtigo){

return 0;
}







