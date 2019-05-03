#include "maAPI.h"


struct ArtigoF
{
    int id;
    int edr_nome; 
    float preco;
};


struct Artigo
{
	int id;
	char* nome;
	float preco;
	int stock;
};



ssize_t readln(int fildes, void *buf, size_t nbyte){//-----------------------FUNCIONAL
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


/*
	Cria estrutura de Artigo a ser guardada no ficheiro ARTIGOS.txt
	.nbArt: numero de bytes lidos até ao final do ficheiro ARTIGOS.txt
	.nbStr: numero de bytes lidos até ao final do ficheiro STOCKS.txt

	.new->id fica com o resultado do nº de bytes lidos até ao final do ficheiro ARTIGOS.txt dividido pelo tamanho da struct que define um artigo
	.new->edr_nome fica com o nº de bytes lidos até ao final do ficheiro STRINGS

	
	NOTA: Esta função não tem o seu prototipo declarado no .h pois é de uso interno da API
*/
ArtigoFile criaStructArtigo(int nbArt, int nbStr,char* price){//---------------FUNCIONAL
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


void insereArtigo(char* nome,char* preco){//-----------------------------------FUNCIONAL
	int fdStr = open("STRINGS.txt", O_CREAT |O_RDWR, 0777);
	int nbStr;
	
	if(fdStr>-1){ 
		nbStr = lseek(fdStr,0,SEEK_END); 
		write(fdStr,nome,strlen(nome));
		write(fdStr,"\n",sizeof(char));
		close(fdStr);
	}else{
		catchMessage(ERROR_1);
	}

	int fdArt = open("ARTIGOS.txt", O_CREAT |O_RDWR, 0777);
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
	int fdStK = open("STOCKS.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	
	if(fdStK>-1){
		write(fdStK,&quant,sizeof(int));
		close(fdStK);
	}else{
		catchMessage(ERROR_3);
	}
}




char* getNome(int edr_nome){//----------------------------------------------FUNCIONAL
int fdStr = open("STRINGS.txt", O_RDONLY, 0777);
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
			catchMessage(MSG_5);
		}
	
	}else{
		catchMessage(ERROR_5);
	}

return 0;
}



/*
	Recebe uma estrutura do tipo Artigo generica e apresenta para o utilizador
	toda a informação desse artigo

	NOTA: Esta função não tem o seu prototipo declarado no .h pois é de uso interno da API
*/
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


Artigo getArtigo(char* id){ //--------------------FUNCIONAL!!!-------APENAS FAZER COM QUE DADO UM ID DE UM ARTIGO que nao existe ESTE NÃO APRESENTE INFORMAÇÃO NENHUMA
int fdArt = open("ARTIGOS.txt", O_RDONLY, 0777);
	
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




void editaPreco(char* id, char* makeItRain){//--------------------------FUNCIONAL
float catchincatchin;
int fdART = open("ARTIGOS.txt",O_RDWR);
	
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




void menuComandos(char* buffer){//-------------------------------------FUNCIONAL
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