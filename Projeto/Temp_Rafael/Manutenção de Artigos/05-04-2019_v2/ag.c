int main(){
int fdVendas = open("VENDAS.txt",O_RDONLY,0777);

	if(fdVendas){
		geraAgregacao();
		close(fdVendas);
	}else{
		catchMessage(ERROR_35);
	}
	return 0;
}