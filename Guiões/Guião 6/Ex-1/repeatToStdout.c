#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <stdlib.h>

int main(){
	char* buffer[1024];
	int n;
	int canal = open("./canais/firstFifo",O_RDONLY,0777);
	
	if(canal>-1){
		while((n = read(canal,buffer,1024))>0){
			write(1,buffer,n);
		}

		close(canal);
		return 0;
	}
	return 1;
}


