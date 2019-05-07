#include "ag.h"
#include "cv.h"
#include "sv.h"



void cvMenuComandos(char* buffer){
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
int countParams = 0;
char* x = "gv";
char* ag = "ag";
	
	while(countParams==0){	

		if(strcmp(param1,x) == 0){
			countParams = 4;
		}else if(strcmp(param1,ag) == 0){
			countParams = 3;
		}else{

			if(param1 && param2){
				countParams = 2;
			}else if(param1 || param2){
				countParams = 1;				
			}

		}
	}

	switch(countParams){
		case 1:
			
			getStockAndPrice(param1);
			write(1,"\n\n",1);
			break;
		case 2:

			atualizaStock(param1,param2);
			write(1,"\n\n",2);
			break;
		case 3:
			geraAgregacao();
			break;
		case 4:
			
			viewVenda(getVenda(param2));
			write(1,"\n\n",2);
			break;
		default:
			system("clear");
			catchMessage(MSG_4);
	}

}

int main(){
char buffer[1024];

	/*
		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	*/
	while(cvReadln(0,buffer,1024)){
		cvMenuComandos(buffer);
	}

return 0;
}