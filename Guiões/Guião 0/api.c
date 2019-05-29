#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*
	Estrutura de dados
*/
struct Pessoa
{
	int id;
	char* nome;
	int idade;
};


void menu(char opt){
clearscr();
	while(opt != 'x'){

		switch(opt)
		{
			case 'a':
				/*Cria a ficha de uma pessoa e guarda a informação*/
				callNew_Person();
				break;

			case 'b':
				/*Colona a informação do cliente devolvendo uma estrutura com os dados do cliente colonado*/
				//call_clone_person();
				break;

			case 'c':
				call_destroy_person();
				break;

			case 'd':
				call_person_age();
				break;

			case 'e':
				call_person_change_age();
				break;

			case 'f':
				/*Imprime todas as fichas de pessoas*/
				printAllPersons();
				break;
			case 'g':
				/*Imprime a ficha de pessoas*/
				call_get_person();
			break;
			case 'x':
				exit(0);

			default:
				printf("Opção invalida!\n");
				callMenuOptions();
				

		}
	}
}




/*
	Função que faz a limpesa do ecra consoante o SO existente
*/
void clearscr(){//<-----------------------------------------------------------------FUNCIONAL
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
   //Podem ser adiconados novos SOs
#else
    #error "Sistema operativo não é suportado!"
    //you can also throw an exception indicating the function can't be used
#endif
}



void callMenuOptions(){//-----------------------------------------------------------FUNCIONAL
	char opt;

	clearscr();
	printf("a - Inserir pessoa(char*, int)\nb - Colonar pessoa(Person)\nc - Eliminar pessoa(Person)\nd - Idade da pessoa(Person)\ne - Alterar idade(Person,int)\n");
	printf("f - Ver todas as pessoas!\ng - Obter informação de uma pessoa(id)\n");
	scanf("%c",&opt);
	menu(opt);
}


void addPerson(Person p){//-----------------------------------------------------------FUNCIONAL
	int fdPersons = open("data_Persons",O_CREAT | O_RDWR | O_APPEND,0777);//<---cria o ficheiro onde serão guardados os dados 
	Person new = malloc(sizeof(struct Pessoa));//<--- só para confirmar que o que foi guardado em ficheiro foi realemente guardado com sucesso

	if(fdPersons>-1){
		write(fdPersons,p,sizeof(struct Pessoa));

		lseek(fdPersons,(-1)*sizeof(struct Pessoa),SEEK_END); 
		read(fdPersons,new,sizeof(struct Pessoa));
		close(fdPersons);
		printPerson(new);
		free(new);
		getchar();//<---para capturar o que estiver em buffer e assim não ser interpretado como comando invalido no menu
		getchar();
	}
		callMenuOptions();

}


void callNew_Person(){//--------------------------------------------------------------------FUNCIONAL
	char* nome = malloc(50*sizeof(char));
	int idade=0;

	printf("Insira o nome da pessoa:\n");
	scanf("%s",nome);
	printf("Insira a idade da pessoa:\n");
	scanf("%d",&idade);

	addPerson(new_person(nome,idade));
}


void printPerson(Person p){//<<-------------------------------------------------------------FUNCIONAL
	char* msg = malloc(100*sizeof(char));
	
	sprintf(msg,"\nID: %d\nNome: %s\nIdade: %d\n\n",p->id, p->nome, p->idade);
	write(1,msg,strlen(msg));
}

char* getNome(int id){
	int fdPersons = open("data_Persons",O_RDONLY,0777);
	char* nome = malloc(50*sizeof(struct Pessoa));

	lseek(fdPersons,id*sizeof(struct Pessoa)+sizeof(int),SEEK_SET);
	readln(fdPersons,nome,50);//<<---------------------------------------------------------------NÃO LÊ A VARIAVEL DIREITO!
	return nome;
}

void printAllPersons(){//<<----------------------------------------------------------------REVER O QUE ESTÁ MAL NESTA FUNCÇÃO!
	int fdPersons = open("data_Persons",O_RDONLY,0777);
	Person new = malloc(sizeof(struct Pessoa));
	int nbTotal = lseek(fdPersons,0,SEEK_END);
	int numPersons = nbTotal/sizeof(struct Pessoa);

	printf("NUmero de pessoas existente: %d\n",numPersons);
	
	for(int i=0; i<numPersons;i++){
		lseek(fdPersons,i*sizeof(struct Pessoa),SEEK_SET);
		read(fdPersons,new,sizeof(struct Pessoa));
		printf("ID: %d\n",new->id);
		printf("Nome: %s\n",getNome(i)); //<--------------------------------------------------- perceber porquê qu não imprime o nome! 
		printf("Idade: %d\n",new->idade);
		
	}
		
	close(fdPersons);
	
}

Person new_person(char* name, int age){//<---------------------------------------------------------FUNCIONAL
	int lastPersonID = 0;
	int fdPersons = open("data_Persons",O_RDONLY,0777);
	Person new = malloc(sizeof(struct Pessoa));

	if(fdPersons>-1){
		lseek(fdPersons,(-1)*sizeof(struct Pessoa),SEEK_END);//<--posiciona-se no inicio da ultima estrutura adicionada
		read(fdPersons,&lastPersonID,sizeof(int));//<--lê o id da pessoa na estrutura

		new->id = lastPersonID+1; //<---o id da pessoa a adicionar será 1 unidade acima da pessoa anterior
		new->nome = malloc(50*sizeof(char));

		strcpy(new->nome,name);
		new->idade = age;
			
		return new;
	}else{//<---- caso nao exista nenhuns dados
		new->id = lastPersonID;
		new->nome = malloc(50*sizeof(char));
		strcpy(new->nome,name);
		new->idade = age;

		return new;
	}
	return NULL;
}

/*
Person clone_person(Person p){//<<----------------------------------------------------------------REVER O QUE ESTÁ MAL NESTA FUNCÇÃO!
	Person new = malloc(sizeof(struct Pessoa));

		new->id=p->id;
		new->nome = malloc(strlen(p->nome)*sizeof(char));
		strcpy(new->nome,p->nome);
		new->idade = p->idade;

		printPerson(new);
		return new;
}

*/


/*
void call_clone_person(){
	int codPerson= -1;

	printf("Insira o codigo da pessoa que deseja colonar:\n");
	scanf("%d",&codPerson);
	clone_person(getPerson(codPerson));
}
*/

void destroy_person(int cod){
	int fdPersons = open("data_Persons",O_RDONLY,0777);

	lseek(fdPersons,cod*sizeof(struct Pessoa),SEEK_SET);
	write(fdPersons,NULL,SEEK_CUR);
	printAllPersons();
	close(fdPersons);
}

void call_destroy_person(){//---------------------------------------------------------------MÁ ABORDAGEM!
	int codPerson= -1;

	printf("Insira o codigo da pessoa que deseja iliminar:\n");
	scanf("%d",&codPerson);
	destroy_person(codPerson);
}

int person_age(int cod){//------------------------------------------------------------------FUNCIONAL
	int fdPersons = open("data_Persons",O_RDONLY,0777);
	Person new = malloc(sizeof(struct Pessoa));

	lseek(fdPersons,cod*sizeof(struct Pessoa),SEEK_SET);
	read(fdPersons,new,sizeof(struct Pessoa));
	close(fdPersons);
	return new->idade;
}

void call_person_age(){//-------------------------------------------------------------------FUNCIONAL
int codPerson=-1;
	printf("Insira o codigo da pessoa que deseja consultar:\n");
	scanf("%d",&codPerson);
	printf("Idade da pessoa:%d\n",person_age(codPerson));
	getchar();
	getchar();
	callMenuOptions();
}


void person_change_age(int p,int age){
	int fdPersons = open("data_Persons", O_RDWR,0777);
	int newIdade=-1;
	lseek(fdPersons,p*sizeof(struct Pessoa)-sizeof(int),SEEK_SET);
	write(fdPersons,&age,sizeof(int));
	lseek(fdPersons,(-1)*sizeof(int),SEEK_CUR);
	read(fdPersons,&newIdade,sizeof(int));
	close(fdPersons);
}

void call_person_change_age(){//---------------------------------------------------------------FUNCIONAL!
	int codPerson= -1;
	int age=-1;
	printf("Insira o codigo da pessoa que deseja alterar a idade:\n");
	scanf("%d",&codPerson);
	printf("Insira o valor da nova idade:\n");
	scanf("%d",&age);

	person_change_age(codPerson,age);
}


Person getPerson(int codPerson){
	int fdPersons = open("data_Persons",O_RDONLY,0777);
	Person new = malloc(sizeof(struct Pessoa));

	lseek(fdPersons,codPerson*sizeof(struct Pessoa),SEEK_SET);
	read(fdPersons,new,sizeof(struct Pessoa));
	close(fdPersons);
		
	return new;
}

void call_get_person(){
	int id=-1;

	printf("Insira o codigo do cliente que quer consultar:\n");
	scanf("%d",&id);
	printf("ID: %d\n",(getPerson(id))->id);
	printf("Nome: %s\n",(getPerson(id))->nome);//<<<-------------------------------------------------------------DÁ ERRO AQUI; NAO APRESENTA O NOME
	printf("Idade: %d\n",(getPerson(id))->idade);
	getchar();
}


ssize_t readln(int fildes, void *buf, size_t nbyte){
  int n;
  char c;
  char *buffer = (char *)buf;
  ssize_t nbytes = 0;//posição inicial de leitura do buffer



  while( nbytes < nbyte && (n = read(fildes,&c,1)) > 0 && c != '\n' ){//enquanto nao carregar o buffer com a quantidade de bytes a ler, ou encontrar um \n ou falhar a leitura 
      buffer[nbytes++] = c; //carrega o caracter lido para o buffer
  }


  if(nbytes < nbyte){//caso o buffer não seja completamente preenchido por encontrar um \n
  	(buffer[nbytes] = '\0');//insere na posição seguinte á ultima lida para o buffer o \0 e assim define o final da string lida 
  }else{
  	(buffer[nbytes-- - 1] = '\0');// caso ocorra uma falha de leitura é feito o reposicionamento do buffer para 
  }

  return nbytes;
}

