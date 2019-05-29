#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>


int main(){
	char buff[1024];
	int n;
	int canal = open("./canais/firstFifo",O_WRONLY,0777);
	
	if(canal>-1){	
	
		while((n = read(0,buff,1024)>0)){
			write(canal,buff,n);
		}
	
		close(canal);
		return 0;
	
	}
	
	return 1;
}


