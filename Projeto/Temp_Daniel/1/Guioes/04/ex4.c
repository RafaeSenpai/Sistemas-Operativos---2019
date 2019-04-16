#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


int main(int argc,char** argv){


	int i=1,fabrir=-1,fsaida=-1;
	// verificar se estao certos os numeros de argumentos
	if(argc<=1){

		printf("Usage: %s [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...",argv[0]);

		return 1;

	}
	// quando encontrar um -i

	if(strcmp(argv[i],"-i")==0){
			// abres um ficheiro que se vai encontrar na posicao i+1
			fabrir = open(argv[i+1],O_RDONLY );
			fazes a copias desse ficheiro para o stdin
			if(dup2(fabrir,0)<0){

				printf("Erro a redirecionar o stdin para %s\n",argv[i+1]);
				return 1;

			}
			// Aumentas o i para 2 unidades para chegar ao -o

			i+=2;


		}
		// quando encontrar um -o
		if(strcmp(argv[i],"-o")==0){
			// abres o ficheiro 

			fsaida = open(argv[i+1],O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR );
			// fazes uma cópia 
			if(dup2(fsaida,1)<0){

				printf("Erro a redirecionar o stdout para %s\n",argv[i+1]);
				return 1;

			}
			//Aumentas o i 2 unidaddes para chegares aos argumentos
			i+=2;


		}
		// fazes exec com argv[i],logo no inicio vai ser o arg1 do enunciado
		// O &argv[i] é o inicio(logo arg1)e o resto portanto vai chegar a um momento em que apanha o NULL tal como é pedido no exec

		execvp(argv[i],&argv[i]);


		// fechas os ficheiros
		close(fsaida);
		close(fabrir);

}
