typedef struct Log{
	char nameFile[50];
	int status;
	int lastAggregateSale;
}LogFile;



/*
	Gere um nome para o ficheiro de agregação com a data e hora corrente aquando a invocação da função
*/
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
void gerarLogFile(char* nameFileAggregation){
	LogFile newLog = malloc(sizeof(struct Log));
	
	strcat(newLog->nameFile,nameFileAggregation);
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
int existLogFIle(){
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