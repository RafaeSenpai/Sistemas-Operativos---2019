#ifndef api_h
#define api_h
#include <sys/types.h>


/*
	Estrutura do artigo no ficheiro artigos
*/
typedef struct ArtigoF *ArtigoFile;


/*
	Estrutura generica do artigo
*/
typedef struct Artigo *Artigo;


/*
	Estrutura de uma Venda no ficheiro Vendas
*/
typedef struct Vendas *Venda;








/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
ssize_t readln(int fildes, void *buf, size_t nbyte);









//-------------API AGREGADOR --------------
/*
	Dado um descritor de ficheiro, neste caso, do ficheiro VENDAS.txt, devolve o numero de vendas existente nesse ficheiro
*/
int getNumVendas(int fd);


/*
	Esta função devolve uma string que apresenta a data e hora f cinalizada com ".txt"
	A string devolvida será usada para criar o nome do ficheiro a ser usado para o descritor
*/
char* nameFileAgregation();


/*
	Cria uma estrutura de venda com o id do artigo, a soma de todas as quantidades vendidas desse artigo e o resultado obtido da soma de todos os totais de venda de todas as vendas desse artigo.
	A obtenção destes resultados a serem guardados na estrutura é feita sobre o ficheiro VENDAS.txt
*/
Venda agCriaStructVenda(int idArtigo, float qtdTotalVendas, float totalVendas);


/*
	Cria uma venda com os valores totais do artigo após a procura de todas as suas vendas no ficheiro VENDAS.txt
	A venda devolvida por esta função será guardada no ficheiro de agregação.

	A função recebe o id do artigo a agregar e o numero de vendas existente no ficheiro VENDAS.txt, este ultimo valor será calculado na função que a chamar.
*/
Venda saleToAgregation(int idArt, int numVendas);

/*
	Dado um ID de artigo, um descritor de ficheiro e o numero de vendas(previamente calculado, de forma a não exigir muito trabalho computacional) 
	verificar se nesse descritor existe o artigo com o dado ID. 
	--------É passado como parametro o descrior de ficheiro porque desta forma posso usar esta a mesma função quer para procurar a existencia de um artigo 
	--------quer nas vendas registadas no ficheiro VENDAS.txt, quer no ficheiro de agregação.

	OBS: - O ficheiro de agregação terá que ser previamente criado
		 - Ao passar os parametros para esta função, o parametro id, deve ser previamente convertido para inteiro, atoi()
		 - A prcura é feita no ficheiro de agregações.
		 - devolve 1 caso o artigo exista ou zero caso não exista.
*/
int existArtInAggregation(int fd, int id, int numArtig);

/*
	EM principio nao sera passado nenhum parametro a esta função
*/
void geraAgregacao();


/*
	Imprimir toda a agregação atual
*/
void viewVendaAggregation(Venda sale);



/*
	Imprimir toda a agregação no ecra
*/
void seeAllAggregation(int fd);





//---------------API Cliente de Vendas ---------------------
void atualizaStock(char* cod, char* qt);

float getPreco(char* id);

Venda criaStructVenda(char* idArt, char* quant);

/*
	Vai buscar uma venda numa determinada posição
	O objetivo desta função não é explorar a necessidade 
	de buscar uma venda pela sua posição do ficheiro. 
	A necessidade desta função é apenas para confirmar, 
	durante os testes á função, se esta está a guardar corretamente os dados
*/
Venda getVenda(char* x);

void viewVenda(Venda x);

void getStockAndPrice(char* id);

void menuComandos(char* buffer);


//-------------API Manutenção de Artigos -------------------

/*
	Cria estrutura de Artigo a ser guardada no ficheiro ARTIGOS.txt
	.nbArt: numero de bytes lidos até ao final do ficheiro ARTIGOS.txt
	.nbStr: numero de bytes lidos até ao final do ficheiro STOCKS.txt

	.new->id fica com o resultado do nº de bytes lidos até ao final do ficheiro ARTIGOS.txt dividido pelo tamanho da struct que define um artigo
	.new->edr_nome fica com o nº de bytes lidos até ao final do ficheiro STRINGS

	
	NOTA: Esta função não tem o seu prototipo declarado no .h pois é de uso interno da API
*/
ArtigoFile criaStructArtigo(int nbArt, int nbStr,char* price);



/*
	Tendo em conta os requisitos exigidos pelo projeto, esta função é considerada 
	uma função interna, pois apenas é usada pela função getStockAndPrice(..), função 
	esta que responde a uma das exigencias do enunciado do projeto. Contudo o 
	seu prototipo encontra-se na API pois pode ter utilidade para o developer para 
	debug se necessário.
*/
float getPreco(char* id);

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
	Recebe uma estrutura do tipo Artigo generica e apresenta para o utilizador
	toda a informação desse artigo

	NOTA: Apesar de se tratar de uma função interna o seu prototipo encontra-se aqui declarado no .h
*/
void viewArtigo(Artigo art);

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


void editaPreco(char* id, char* makeItRain);


void maMenuComandos(char* buffer);
//------------------------------------------FIM API Manutenção de artigos --------------------------------------
#endif
