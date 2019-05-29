#include <stdio.h>

int main(int argc, char** argv){

	for(int i=0; argv[i]!=NULL; i++){
		printf("%dº argumento: %s\n",i+1,argv[i]);
	}
	return 0;
}