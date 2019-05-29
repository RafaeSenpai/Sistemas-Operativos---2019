#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int  main(){
	char temp;

	while(read(0,&temp,1)>0){
		write(1,&temp,1);
	}

	return 0;
}