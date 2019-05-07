

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


ssize_t cvReadln(int fildes, void *buf, size_t nbyte){
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




//------API Manutenção de artigos------
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
//------------------------------------------------------------------------------------------------------








//-------------------------API cliente de vendas ------------------------------------------
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
int fdSTK = open("STOCKS.txt",O_RDWR);
int qtdAtual = 0;
int newStock = 0;


	if(fdSTK>-1){
		int nbLocal = lseek(fdSTK, atoi(cod)*sizeof(int),SEEK_SET);
		int nbEnd = lseek(fdSTK,0,SEEK_END);
		
		if(nbLocal<nbEnd){
			int fdVendas = open("VENDAS.txt",O_CREAT | O_RDWR | O_APPEND,0777);
			
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
					close(fdSTK);//<--- até aqui trata do stock(tudo correto)

					

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
int fdVendas = open("VENDAS.txt",O_RDONLY);
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

/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
int cvGetStock(char* id){ //-------------------------------------------------------FUNCIONAL
int fdStK = open("STOCKS.txt", O_RDONLY);
int stk;

	if(fdStK){
		int nbLocal = lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
		int nbEnd = lseek(fdStK,0,SEEK_END);

		if(nbLocal<nbEnd){
			lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
			read(fdStK,&stk,sizeof(int));
			close(fdStK);
			return stk;
		}else{
			close(fdStK);
			catchMessage(MSG_5);
		}

	}else{
		catchMessage(ERROR_10);
	}

	return 0;
}


/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
float getPreco(char* id){
int fdART = open("ARTIGOS.txt",O_RDWR);
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



void getStockAndPrice(char* id){ //---------------------------------------------FUNCIONAL
char* msg = malloc(100 * sizeof(char));
int fdART = open("ARTIGOS.txt",O_RDWR);

	if(atoi(id)>=0){		
		if(fdART){
			int nbLocal = lseek(fdART,atoi(id)*sizeof(struct ArtigoF),SEEK_SET);
			int nbEnd = lseek(fdART,0,SEEK_END);
			
			if(nbLocal<nbEnd){
				sprintf(msg,"Stock: %d\nPreço: %.2f\n\n",cvGetStock(id),getPreco(id));
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







void cvMenuComandos(char* buffer){//----------------------------------------------FUNCIONAL
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
//--------------------------------------------------------------------------------------------






/*
	exit(0) indicates successful program termination & it is fully portable
	exit(1) (usually) indicates unsucessful termination. However, it's usage 
			is non-portable.

	Note that the C standard defines EXIT_SUCCESS and EXIT_FAILURE to return 
	termination status from a C program.

	0 and EXIT_SUCCESS are the values specified by the standard to indicate 
	successful termination, however, only EXIT_FAILURE is the standard value 
	for returning unsucessful termination. 1 is used for the same in many 
	implementations though.
*/
void catchMessage(char *msg){
	write(1, msg,strlen(msg));
	//exit(1); //<----------------------pode vir ater implicações quando usar concorrencia, talvez!
}
