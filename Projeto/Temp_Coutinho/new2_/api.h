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
	EStrutura que integra o ficheiro log
*/
typedef struct Log *LogFile;

/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
ssize_t readln(int fildes, void *buf, size_t nbyte);



//-------------API AGREGADOR --------------

/*
	Esta função devolve uma string que apresenta a data e hora f cinalizada com ".txt"
	A string devolvida será usada para criar o nome do ficheiro a ser usado para o descritor
*/
char* nameFileAgregation();

/*
	Cria o ficheiro log e adiciona á estrura contida nesse ficheiro o nome da ultima agregação feita

	OBS:
		nameFile: é o nome do ultimo ficheiro de agregação criado

		status: indica se a agregação com nome indicado na estrutura (nameFile) foi devidamente concluida ou não
			0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
			1 - Foi concluida com exito a agregação indicada em nameFile

		lastAggregateSale: indica a posição no ficheiro vendas em que foi interrompida ou finalizada a agregação indicada em nameFile

*/
void gerarLogFile(char* nameFileAgg);

/*
	captura do ficheiro log o nome do ficheiro de agregação
*/
char* getAggregationFileName();

/*
	captura do ficheiro log o valor do status da ultima agregação

	status: indica se a agregação com nome indicado na estrutura (nameFile) foi devidamente concluida ou não
		0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
		1 - Foi concluida com exito a agregação indicada em nameFile
*/
int getLogStatus();

/*
	captura do ficheiro log o numero da posição da ultima venda que foi agregada
*/
int getLogLastAggregateSale();

/*
	Guarda no já existente ficheiro log o novo nome do ficheiro de agregação
*/
void setLogNewAggregationFileName(char* newName);

/*
	Altera no já existente ficheiro log o status para o valor enviado como parametro:

	status: indica se a agregação com nome indicado na estrutura (nameFile) foi devidamente concluida ou não
		0 - Não foi concluida com exito a agregação indicada em nameFile (ex: pode ser o caso em que foi interrompida a meio)
		1 - Foi concluida com exito a agregação indicada em nameFile
*/
void setNewStatus(int newStatus);

/*
	Altera no já existente ficheiro log o valor da posição onde se encontra a ultima venda do ficheiro vendas que foi agregada
*/
void setLastAggregateSale(int newPosition);

/*
	Verifica se existe algum ficheiro log já criado
*/
int existLogFile();

/*
	Dada uma venda devolve a o numero de unidades vendidas nessa venda
*/
float getQuantidade(Venda sale);

/*
	Dada uma venda devolve o valor total da venda dessa venda
*/
float getValTotal(Venda sale);

/*
	Dada uma venda devolve a referencia do artigo nessa venda
*/
float getIDArtigo(Venda sale);

/*
	Recebido o descritor de ficheiro referente ao ficheiro das vendas (VENDAS) devolve o total de vendas existentes nesse ficheiro
*/
int getNumVendas(int fdVendas);

/*
	Imprimir toda a agregação atual
*/
void viewVendaAggregation(Venda sale);

/*
	Imprimir toda a agregação no ecra
*/
void seeAllAggregation(int fd, int nArtInAgg);

/*
	Dada uma posição de uma venda no ficheiro de vendas, devolve a respetiva venda
*/
Venda getVendaToAggregation(int numVenda);

/*
	Função responsavel por iterar sobre o ficheiro das vendas e ir preenchendo o ficheiro de agregação com as vendas agregada.

	Processo:
			1º Passo: É calculado o numero de vendas existentes em todo o ficheiro de vendas, tal informação será util para saber quantas vezes se irá iterar sobre o ficheiro de vendas;
			2º Passo: Sobre o ficheiro "vendas" é feita a consulta da venda que se encontra na posição seguinte á posição(nLasteSale) que é passada por parametro;
			3º Passo: É obtida e armazenda em variaveis toda a informação dessa mesma venda, nomeadamente:
				- id do artigo(inteiro natural incluindo zero);
				- numero de unidades registadas nessa venda;
				- total da despesa da venda

			4º Passo: Acede-se ao ficheiro de agregação e desloca-se sobre o mesmo para a posição indicada pelo proprio id do artigo;
				NOTA: A posição no ficheiro de agregação onde será guardada a venda agregada é ditada pelo offset calculado
					  atravez do produto do idArtigo com o tamanho da estrutura venda(struct Vendas)

			5º Passo: Verifica-se, no ficheiro de agregação, se na posição determinada no passo anterior existe ou não já uma venda escrita, tal conclusão irá
			   		  incidir sobre um de dois processos distintos:
						1º Opção [Caso não exista nenhuma venda escrita na posição]
							- A venda consultada no ficheiro vendas é simplesmente guardada no ficheiro de agregação na pre-determinada posição e termina o
							  processo de agregação para esta venda.
						2º Opção [Caso já exista uma venda registada na posição]
							- A venda já existente é carregada para uma variavel do tipo estrutura de venda (Venda sale) e em seguida são feitas as somas dos valores
							  contidos nessa estrutura com os valores armazenados em variaveis no 3º Passo, tais resultados são guardados na estrutura para que desta
							  forma se proceda á gravação dessa mesma estrutura (Venda sale) na devida posição do ficheiro de agregação.
			6º No ficheiro log, imediatamente após a gravação da venda agregada, é atualizado o valor da ultima venda agregada(nLastSale);

			7º Se todo o processo de agregação for devidamente concluido a flag STATUS no ficheiro log é atualizada para o valor 1;
*/
int runAggregation();

/*
	Apresenta todo o conteudo do ficheiro log
*/
void seeContentLog();

/*
	Esta função é responsavel por verificar as condições em que se encontra o sistema e consoante as mesmas preparar todos os requisitos necessários
	para iniciar ou continuar corretamente a agregação propriamente dita.

	Verificações:
				1º - Verifica se já existe um ficheiro log, este ficheiro é responsavel por armazenar a informação referente a:
					a) Nome do ultimo ficheiro de agregação que foi criado;
					b) Numero da ultima venda que foi incluida no ficheiro de agregação referido no ponto a);
					c) Estado com que a agregação foi terminada (Status), tal estado é representado por um inteiro de valor 1 ou 0:
						  		0 - Não foi concluida com exito a agregação indicada em nameFile (ex: Tratar-se do caso em que a agregação é interrompida a meio)
								1 - Foi concluida com exito a agregação indicada em nameFile

				2º - Caso não exista o ficheiro log, tal situação revela que até a momento não foi feita nenhuma agregação, é então criado um ficheiro log,
					 com o nome do ficheiro de agregação que será criado, o valor da ultima venda agregada terá obviamente o valor zero uma vez que sendo a primeira
					 vez que a agregação irá ser corrida sobre o ficheiro de vendas tais iterações iniciar-se-ão a partir do inicio do ficheiro, e o estado da agregação, status,
					 iniciar-se-á com valor 1, desta forma caso a 1º agregação a ser feita seja interrompida a flag status já indicará que o processo de agregação
					 não foi devidamente concluido.
					 De referir que este ultimo valor, sempre que é ordenada uma nova agregação é imediatamente colocado a 1 e só após uma completa agregação é que é
					 alterada para o valor zero, desta forma o programa saberá se deve iniciar uma nova agregação ou continuar a trabalhar sobre o ficheiro de agregação
					 criado numa "sessão" anterior;

				3º - Dá-se então inicio ao processo de agregação invocando a função runAggregation(char*,int), a função responsavel pela agregação receberá como parametros os
					 dados previamente definidos no ficheiro log, nomeadamente o nome do ficheiro de agregação e a posição onde terminou ou foi interrompida a ultima agregação.
*/
void gerarAgregacao();



//---------------API Cliente de Vendas ---------------------
/*
	Vai buscar uma venda numa determinada posição
	O objetivo desta função não é explorar a necessidade
	de buscar uma venda pela sua posição do ficheiro.
	A necessidade desta função é apenas para confirmar,
	durante os testes á função, se esta está a guardar corretamente os dados
*/
Venda getVenda(char* x);

void atualizaStock(char* cod, char* qt);

Venda criaStructVenda(char* idArt, char* quant);

float getPreco(char* id);

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
#endif
