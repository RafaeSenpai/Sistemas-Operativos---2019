#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int n, int m, int mtx[n][m]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++)
			printf("|  %d  |", mtx[i][j]);
		putchar('\n');
	}
}

void gerate(int n, int m, int mtx[n][m]){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			mtx[i][j] = rand() % 10;
}

int contains(int m[], int n, int x){
	int found = 0;

	for(int i = 0; i < n && !found; i++)
		if(m[i] == x)
			found = 1;
	return found;
}

int main(int argc, char **argv){
	int i = atoi(argv[1]);
	int j = atoi(argv[2]);
	int search = rand() % 10;
	int ps, status, found = 0;
	int mx[i][j];
	pid_t pid;
	gerate(i, j, mx);//gera matriz
	
	for(ps = 0; ps < i; ps++){//precorre todas as linhas da matriz
		pid = fork();
		if( pid == -1 ){
			perror("Fork failed!");
			return 1;
		} 
		if( pid == 0 ){
			printf("Valor a procurar na matriz: %d\n",search);
			found = contains(mx[ps],j,search);//atribui ao processo filho corrente a tarefa de procurar na linha atual da matriz o valor de aleatorio 'search'
			printf("Resultado da procura na linha(0-Não existe/1-Existe): %d\n",found);
			_exit(found);//termina o processo filho corrente submetendo o valor logico da procura feita(1-valor encontrado / 0-valor não encontrado)
		}
	}

	for(ps = 0; ps < i; ps++){
		pid = wait(&status);/*<<-- bloqueia a execução do processo pai até o filho terminar e em caso de sucesso devolve o PID o filho correspondente e 'status' 
								   é atualizado com o codigo de terminação do processo filho (valor de 'found', isto é 0 ou 1 caso tenha ou nao encontrado o valor 
								   a procurar)*/
		printf("Valor do 'found: %d\n",found);
		found = found || WEXITSTATUS(status);
		printf("WEXITSTATUS(): %d\n",WEXITSTATUS(status));
		printf("found || WEXITSTATUS(status) = %d\n",found);
	}

	printMatrix(i,j,mx);
	printf("Search := %d\n", search);
	printf("Found  := %d\n", found);
	return 0;
}