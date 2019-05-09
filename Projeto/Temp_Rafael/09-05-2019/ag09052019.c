/*
	EStrutura que integra o ficheiro log
*/
typedef struct Log{
	char nameFile[50];
	int status;
	int lastAggregateSale;
}LogFile;



/*
	Cria um nome para o ficheiro de agregação com a data e hora corrente aquando a invocação da função
*/
char* nameFileAggregation(){
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
	Cria o ficheiro log e adiciona á estrura contida nesse ficheiro o nome da ultima agregação feita

	OBS:
		nameFile: é o nome do ultimo ficheiro de agregação criado

		status: indica se a agregação com nome indicado na estrutura (nameFile) foi devidamente concluida ou não
			0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
			1 - Foi concluida com exito a agregação indicada em nameFile
		
		lastAggregateSale: indica a posição no ficheiro vendas em que foi interrompida ou finalizada a agregação indicada em nameFile

*/
void gerarLogFile(char* nameFileAgg){
	LogFile newLog = malloc(sizeof(struct Log));
	
	strcat(newLog->nameFile,nameFileAgg);
	newLog->status = 0;
	newLog->lastAggregateSale = 0;

	int fdLog = open("log",O_CREAT | O_RDWR,0777);
	lseek(fdLog,0, SEEK_SET);
	write(fdLog, newLog,sizeof(struct Log));
	close(fdLog);
	free(newLog);
}


/*
	captura do ficheiro log o nome do ficheiro de agregação	
*/
char* getAggregationFileName(){
	int fdLog = open("log",O_RDONLY,0777);
	char nomeFicheiro[50];

		lseek(fdLog,0,SEEK_SET);
		read(fdLog,nomeFicheiro,50*sizeof(char));//<<<<----------pode vir a dar erro aqui!
		close(fdLog);

	return nomeFicheiro;
}


/*
	captura do ficheiro log o valor do status da ultima agregação

	status: indica se a agregação com nome indicado na estrutura (nameFile) foi devidamente concluida ou não
		0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
		1 - Foi concluida com exito a agregação indicada em nameFile
*/
int getLogStatus(){
	int fdLog = open("log",O_RDONLY,0777);
	int status = -1;

		lseek(fdLog,(-2)*sizeof(int),SEEK_END);//<<<<<<-------------PODE DAR ERRO AQUI pq (-2)*sizeof(int) = sizeof(int) + sizeof(int) 
		read(fdLog,&status,sizeof(int));
		close(fdLog);

	return status;
}


/*
	captura do ficheiro log o numero da posição da ultima venda que foi agregada
*/
int getLogLastAggregateSale(){
	int fdLog = open("log",O_RDONLY,0777);
	int lastAggregateSale = -1;
	
		lseek(fdLog,(-1)*sizeof(int),SEEK_END);
		read(fdLog,&lastAggregateSale,sizeof(int));
		close(fdLog);

	return lastAggregateSale;
}


/*
	Guarda no já existente ficheiro log o novo nome do ficheiro de agregação
*/
void setLogNewAggregationFileName(char* newName){
	int fdLog = open("log",O_WRONLY,0777);
	LogFile new = malloc(sizeof(struct Log));

		read(fdLog,new,sizeof(struct Log));
		strcpy(new->nameFile,newName);//<<<<-------------pode dar erro aqui!
		lseek(fdLog,0,SEEK_SET);
		write(fdLog,new,sizeof(struct log));
		close(fdLog);
		free(new);
}


/*
	Altera no já existente ficheiro log o status para o valor enviado como parametro:

	status: indica se a agregação com nome indicado na estrutura (nameFile) foi devidamente concluida ou não
		0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
		1 - Foi concluida com exito a agregação indicada em nameFile
*/
void setNewStatus(int newStatus){
	int fdLog = open("log",O_WRONLY,0777);

	lseek(fdLog, (-2)*sizeof(int),SEEK_END);
	write(fdLog,&newStatus,sizeof(int));
	close(fdLog);
}


/*
	Altera no já existente ficheiro log o valor da posição onde se encontra a ultima venda do ficheiro vendas que foi agregada
*/
void setLastAggregateSale(int newPosition){
	int fdLog = open("log",O_WRONLY,0777);

	lseek(fdLog,(-1)*SIZEOF(INT),SEEK_END);
	write(fdLog,&newPosition,sizeof(int));
	close(fdLog);

}


/*
	Verifica se existe algum ficheiro log já criado
*/
int existLogFile(){
	int fdLog = open("log",O_WRONLY,0777);

	if(fdLog<0){
		close(fdLog);
		return 0;
	}
	//close(fdLog);
	return 1;
}


/*
	Dada uma venda devolve a o numero de unidades vendidas nessa venda
*/
float getQuantidade(Venda sale){
	return sale->quant;
}


/*
	Dada uma venda devolve o valor total da venda dessa venda
*/
float getValTotal(Venda sale){
	return sale->vTotal;
}


/*
	Dada uma venda devolve a referencia do artigo nessa venda
*/
float getIDArtigo(Venda sale){
	return sale->idArt;
}


/*
	Recebido o descritor de ficheiro referente ao ficheiro das vendas (VENDAS) devolve o total de vendas existentes nesse ficheiro	
*/
int getNumVendas(int fdVendas){
	int totBytes = lseek(fdVendas,0,SEEK_END);
	
		close(fdVendas);

	return totBytes/(sizeof(struct Vendas));
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


/*
	Dada uma posição de uma venda no ficheiro de vendas, devolve a respetiva venda 
*/
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
	int fdVendas = open("vendas",O_RDONLY,0777);
	Venda sale = malloc(sizeof(struct Venda));

		int nTotalDeVendas = getNumVendas(fdVendas);
		close(fdVendas);

		nLastSale++;//<<<-----para não agregar novamente a ultima venda que tinha sido agregada na ultima agregação

		for(;nLastSale<=nTotalDeVendas;nLastSale++){ //<<----pode dar erro aqui por causa do <= ou por causa do for(;...)
			sale = getVendaToAggregation(nLastSale);

			int idArtV = getIDArtigo(sale);
			float qtV = getQuantidade(sale);
			float valTotV = getValTotal(sale);

			int fdAgg = open(aggFileName,O_RDWR,0777);
			lseek(fdAgg,idArtV*sizeof(struct Vendas),SEEK_SET);

			if((read(fdAgg,sale,sizeof(struct Vendas)))<0){//<<---seja já existir uma venda naquela posição ele vai guardar o conteudodessa venda para a estrutura"sale" e devolver um valor >0, se não existir nenhuma venda naquela posição entao não vai guardar nada para a estrutur sale e vai devolver um valor >0
				write(fdAgg,getVendaToAggregation(nLastSale),sizeof(struct Vendas));	 
				setLastAggregateSale(nLastSale-1);
				free(sale);
			}else{//<<---caso já exista outra venda do mesmo artigo naquela posição no ficheiro de agregação
				sale->idArt = idArtV;
				sale->quant += qtV;
				sale->vTotal += valTotV;
				write(fdAgg,sale, sizeof(struct Vendas));
				setLastAggregateSale(nLastSale-1);
				free(sale);
			}
		}
		setNewStatus(1);
	return fdAgg;
}



void gerarAgregacao(){

	if(existLogFile()==1){//<<--caso exista um ficheiro log já criado
		if(getLogStatus()==1){//<<--a ultima agregação foi concluida com sucesso
			setLogNewAggregationFileName(nameFileAggregation());
			setNewStatus(0); //<<---0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
			seeAllAggregation(runAggregation(getAggregationFileName(),getLogLastAggregateSale()));
		}else{//<<--- casp a ultima agregação não tenha sido concluida com sucesso
			seeAllAggregation(runAggregation(getAggregationFileName(),getLogLastAggregateSale()));
		}
	}else{//<<---caso não exista nenhum ficheiro log
		gerarLogFile(nameFileAggregation());
		seeAllAggregation(runAggregation(getAggregationFileName(),getLogLastAggregateSale()));
	}
}

