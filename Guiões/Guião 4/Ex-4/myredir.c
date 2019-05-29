#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

ssize_t readln(int fildes, void *buf, size_t nbyte){
ssize_t i=0;
int n;
char tmp;
char *buffer = (char *)buf;
	
	while((n = (read(fildes,&tmp,1)>0)) && i<nbyte){
		buffer[i]=tmp;
		i++;
		if(tmp == '\n'){//quando o caracter adicionado ao buffer for \n é porque jáleu até ao final da linha e entao termina o while (processo de leitura da linha)
			break;
		}
	}

	if(i<nbyte){
		buffer[i] = '\0';
	}else{//caso seja igual (caso em que esgotou o numero de bytes que podiam ser lidos - este parametro é o parametro que é dado pela variavel nbytes)
		buffer[i-1] = '\0';
	}
	//printf("Retorno do readln: %d\n",);
	return i;
}


int main(int argc, char** argv){
int flag = 0;
char buff[1024];

	for(int i=0; i<argc; i++){
		printf("%dº - Argumento: %s\n",i+1,argv[i]);
	}

	int fdE = open("erros.txt", O_CREAT | O_RDWR , 0777);
	
	dup2(fdE,2);
	close(fdE);

		if((strcmp(argv[1],"-i")==0) && (strcmp(argv[3],"-o")==0)){//é definido output
			int fdIn = open(argv[2],O_RDONLY,0777);
			int fdOut = open(argv[4],O_CREAT | O_RDWR,0777);
			flag=1;
			printf("Redirecionamento do input e output!\n");
			if(fdIn>-1){
				dup2(fdIn,0);
				if(fdOut>-1){
					readln(fdIn,&buff,1024);
					lseek(fdIn,0,SEEK_SET);
					dup2(fdOut,1);
					close(fdIn);
				}else{
					perror("Erro no descritor de Output!\n");
				}
			}else{
				perror("Erro no descritor de input!\nO descritor de output também não foi criado!");
			}

		}else if((strcmp(argv[1],"-i")==0) && (strcmp(argv[3],"-o")!=0)){//nao é definido output
			int fdIn = open(argv[2],O_CREAT |O_RDONLY,0777);
			flag = 2;/*<<<--para mais á frente dar inidicação que é para ter em conta a nova posição do 
							argv que se encontra a indicar o ficheiro que a função invocada irá receber de input*/
			printf("Redirecionamento do input!\n");
			if(fdIn>-1){
				readln(fdIn,&buff,1024);
				lseek(fdIn,0,SEEK_SET);
				dup2(fdIn,0);
				close(fdIn);
			}else{
				perror("Erro nos descritores de input!\n");
			}
		}else if(strcmp(argv[1],"-o")==0){//é definido output
				int fdOut = open(argv[2],O_CREAT | O_RDWR,0777);
				flag=3;
				printf("Redirecionamento do Output!\n");
				if(fdOut>-1){
					dup2(fdOut,1);
					close(fdOut);
				}else{
					perror("Erro nos descritores de output!\n");
				}
			}else{
				printf("Não existem redirecionamentos!\n");
				flag=4;
			}

	int status;
	pid_t pid;
	pid = fork();

	if(pid<0){
		perror("Não consegui gerar o filho!\n");
		return 1;
	}
	if(pid==0){
	
		if(flag==1){//é definido input (o input contem funções a ser execuadas) e output para a função
			execlp(buff,argv[5],argv[2],NULL);//apenas se for uma função do preloud e sem opções extra da função invocada
		}else if(flag==2){//é definido input mas nao o output
			execlp(buff,buff,NULL);//apenas se for uma função do preloud e sem opções extra da função invocada
		}else if(flag==3){//definindo apenas o output
			execlp(argv[3],argv[3],argv[4],NULL);
		}else
		_exit(0);
	
	}else{
	
		pid = wait(&status);
		return status;
	
	}

	return 0;		
}

/*padrões funcionais:

	./myredir -i <ficheiro 1> -o <ficheiro 2>
		*o ficheiro 1 contem instruçoes que serão executadas e seu resultado guardado no ficheiro 2

	./myredir -o <ficheiro 1>	<função do sistema>
		* o resultado da função será guardado no ficheiro 1

	./myredir -o <ficheiro 1>	<função do sistema>	<ficheiro input da função do sistema>
		* o resultado da função será guardado no ficheiro 1
*/