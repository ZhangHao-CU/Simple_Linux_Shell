#include "simple_sh.h"

void clear_history(char **history)
{
	int i = 0;
	while (history[i] != NULL) {
		/*write(1, history[i], strlen(history[i]));*/
		/*write(1, "\n", 1);*/
		free(history[i]);
		history[i] = NULL;
		i++;
	}
}
