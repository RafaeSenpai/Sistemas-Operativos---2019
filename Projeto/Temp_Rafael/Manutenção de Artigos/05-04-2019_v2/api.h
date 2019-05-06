

/*
	Estrutura do artigo que é guardada no ficheiro artigos
*/

typedef struct ArtigoF *ArtigoFile;


/*
	Estrutura generica do artigo.
	É constituida por todos os atributos de um artigo sem ser por qualquer tipo de referenciação.
*/
typedef struct Artigo *Artigo;



/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
ssize_t readln(int fildes, void *buf, size_t nbyte);




/*
	Dado o nome e o preço de artigo, é adicionada a informação do mesmo no ficheiro ARTIGOS.txt, nomeadamente 
	os atributos, ID, nome e preço (guardados numa struct). Também é criado um ficheiro STRINGS.txt com o 
	respetivo nome do produto e outro ficheiro com o respetivo stock do mesmo.
	Os atributos da estrutura guardada em ARTIGOS.txt:
	-ID
	-edr_nome
	-preco
*/
void insereArtigo(char* nome,char* preco);


/*
	Dado a posição do nome de um artigo no ficheiro STRINGS.txt, vai buscar o nome (string) desse artigo ao ficheiro STRINGS.txt
*/
char* getNome(int id);


/*
	Dado o ID de uma artigo devolve o stock do mesmo.
	Se não existir o ID inserido retorna 0.
*/
int getStock(int id);


/*
	Dado o ID de um artigo, devolve uma estrutura (generica) do artigo, isto é devolve 
	uma estrutura com os seguintes atributos:
	-ID;
	-Nome;
	-Preço
	-Stock.
	
	A justificação do porquê devolver uma estrutura generica do artigo é porque esta torna possivel ao utilizador, que não esteja contextualizado 
	com a estrutura de dados ARTIGO que é guardada em ficheiro, uma facil leitura de todas as caracteristicas do produto.
*/
Artigo getArtigo(char* id);


void editaNome(char* id, char* nome);


void menuComandos(char* buffer);


/*
	Responsavel por encaminhar as mensagens de erro para as devidas funções.
	Foi criado a pensar em facilitar a deteção de algum erro durante os testes com varios clientes em simultaneo
*/
void catchMessage(char *msg);

#endif

