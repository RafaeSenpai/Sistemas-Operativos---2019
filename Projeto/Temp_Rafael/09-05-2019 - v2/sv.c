#include "api.h"

int main(){
char buffer[1024];

	/*
		Reformular esa main!
	*/
	while(readln(0,buffer,1024)){
		menuComandos(buffer);
	}

return 0;
}