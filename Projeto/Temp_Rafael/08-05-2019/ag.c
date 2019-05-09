//-----------------API AGREGADOR -------------------
char* nameFileAgregation(){//---------------------------------------------------------------------------------------SUPOSTAMENTE OPERACIONAL
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


#define SaleFile "vendas"
#define LogFile "logFILE"


typedef struct logAggregation{
	int status; //1-caso a ultima agregação tenha sido feita com sucesso; 0-caso a ultima agregação NÃO tenha sido concluida com sucesso
	char nome[80]; //nome do ultimo ficheiro de agregação gerado
	int numVenda; //numero da ultima venda que foi agregada
} structLog;

structLog geraStructLog(int state, char* name, int nVenda){
	geraStructLog newLog = malloc(sizeof(struct logAggregation));
	
	newLog->status = state;
	strcpy(newLog->nome,name);
	newLog->numVenda = nVenda;
return newLog;
}

void atualizaLog()


void gerarAgregacao(){//lPAggregation: posição no ficheiro vendas referente á ultima venda que foi agregada na ultima agregação gerada
int fdLog = open(LogFile,O_RDWR,0777); //abre o ficheiro log em modo escrita, se este não existir devolve um valor <0
int fdVendas = open(SaleFile,O_RDONLY,0777);//abre o ficheiro de vendas

	char* nomeFicheiroAgr = malloc(50*sizeof(char));//gera uma string que seŕa o nome do novo ficheiro de agregação
	strcpy(nomeFicheiroAgr,nameFileAgregation());


	if(fdLog<0){ //caso não exista um ficheiro log, quer dizer que não foi feita até ao momento nenhuma agregação
		fdLog = open(LogFile,O_CREATE | O_RDWR,0777);//cria previamente o ficheiro log, que será usado para guardar a posição no descritor de ficheiro VENDAS onde foi interropida a ou onde a foi terminada a agregação. 
		newLog log = geraStructLog(0,nomeFicheiroAgr,0);
		write(fdLog,log,sizeof(struct logAggregation));
	}else{//caso exista o ficheiro log, este então contem a informação do numero da ultima venda agregada








	if(fdVendas>-1){
		int nbTotal = lseek(SaleFile,0,SEEK_END);
			lseek(fdLog,0, SEEK_SET); 
			read(fdLog,&lPAggregation,sizeof(int));//vou buscar o numero da ultima venda que foi agregada 
		}

		int aggregationFile = open(nameFileAgregation(),O_CREAT | O_RDWR | O_APPEND, 0777); //<<--- é criado o ficheiro de agregação com o nome igual á data do momento em que é gerada a agregação

		if(aggregationFile>-1){
			for(lPAggregation; (lPAggregation*sizeof(struct Vendas)) < nbTotal; lPAggregation++){//enquanto não chegar ao final do ficheiro

		}else{
			"ERRO A INFORMAR QUE FALHOU NA ABERTURA DO DESCRITOR DE FICHEIROS DO FICHEIRO DE AGREGAÇÃO"
		}

}