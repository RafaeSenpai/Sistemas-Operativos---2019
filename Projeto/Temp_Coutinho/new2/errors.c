#include "errors.h"

void catchError(char *msg){
	write(1, msg,strlen(msg));
	exit(1);
}