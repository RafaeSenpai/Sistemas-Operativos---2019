#include "notifications.h"
#include <string.h> //strlen - strcpy - strtok - strcmp
#include <unistd.h> //system calls
//-----------------------------API Notifications----------------------------------


/*
	exit(0) indicates successful program termination & it is fully portable
	exit(1) (usually) indicates unsucessful termination. However, it's usage 
			is non-portable.

	Note that the C standard defines EXIT_SUCCESS and EXIT_FAILURE to return 
	termination status from a C program.

	0 and EXIT_SUCCESS are the values specified by the standard to indicate 
	successful termination, however, only EXIT_FAILURE is the standard value 
	for returning unsucessful termination. 1 is used for the same in many 
	implementations though.
*/
void catchMessage(char *msg){
	write(1, msg,strlen(msg));
	//exit(1); //<----------------------pode vir ater implicações quando usar concorrencia, talvez!
}


//------------------------------FIM API Notifications-----------------------------------------------


