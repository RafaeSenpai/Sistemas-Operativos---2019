#include "api.h"
#include <fcntl.h> //file descriptor
#include <unistd.h> //system calls
#include "notifications.h"

#define SaleFile "vendas"

int main(){
	int fdVendas = open(SaleFile,O_RDONLY,0777);

	if(fdVendas){
		gerarAgregacao();
		close(fdVendas);
	}else{
		catchMessage(ERROR_35);
	}
	return 0;
}
