#include <unistd.h>//fork/getpid()/getppid()
#include <stdio.h>//printf
#include <sys/wait.h>//fork/getpid()/getppid()/wait()
#include <stdlib.h>//malloc
#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"


/*
void execute(){

	execv(cenas,NULL);
}
*/
/*decompor em palavras e enviar a atual palavra capturada para um filho*/
int mySys(char* command){
int i;	
char*  cmd = malloc(20 * sizeof(char));

	for(i = 0; command[i]!='\0'; i++){
		while(command[i]== ' ' && command[i]!='\0'){
			i++;
		}

		if(command[i]=='\0'){
			return i;

		}else{

			cmd = strtok(command," ");//ou  strcat(cmd,strtok(command," "));

			pid_t pid = fork();
			if(pid<0){
				printf("Não consegui gerar o filho para correr o comando!\n");
			}
			if(pid==0){
				printf("comando:%s\n",cmd);
				execl(cmd," ",NULL);
				_exit(0);
			}
		}
	}
	return i;
}


int main(int argc, char** argv){
char* command = malloc(1024*sizeof(char));


	for(int i=1; i<argc; i++){ //compoem a string que irá conter a função a ser chamada e os suas posiveis flags 
		strcat(command,argv[i]);
		if(argv[i+1]){
			strcat(command," ");
		}
	}
	

	printf("COMANDO: %d\n",mySys(command));

	return mySys(command);
	
return 0;
}

