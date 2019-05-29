#include <unistd.h>

int main(int argc, char** argv){

	execvp("./programa_Executavel/argstoArray",argv);

	return 0;
}