#include "simple_sh.h"

void add_history(int *counter, char **history, char *command)
{
	if (history[*counter] != NULL) {
		free(history[*counter]);
		history[*counter] = NULL;
	}
	history[*counter] = malloc(sizeof(char)*(strlen(command)+1));
	strncpy(history[*counter], command, strlen(command));
	/*history[*counter][length-1] = '\0';*/
	*counter = (*counter+1)%100;
}
