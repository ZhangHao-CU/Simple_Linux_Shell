#include "simple_sh.h"
/*we set this number(1024) to take any length of buffer input, if the actual length exceeds this number, the program still works but have some memory leak problems.*/

int interpret_input(char *buf, char **parameters)
{
	int counter=0;
	int j =0;
	char **items;
	char *s, *name;
	items = malloc(sizeof(char *)*(COMMAND_ARGV_MAX+1));
	for (j=0; j < COMMAND_ARGV_MAX; j++) {
		if (parameters[j] != NULL) {
			free(parameters[j]);
			parameters[j] = NULL;
		}
	}
	interpret_line(buf, "|\n", items);
	j=0;
	while (items[j] != NULL) {
		s = strdup(items[j]);
		while (1) {
			name = strsep(&s, " ");
			if ((name != NULL) && (strcmp(name, "\0") != 0)) {
				parameters[counter] = malloc(sizeof(char)*(strlen(name)+1));
				strcpy(parameters[counter], name);
				counter++;
				if (counter >= COMMAND_ARGV_MAX) {
					return -1;
				}
			}
			else if (name == NULL) {
				break;
			}
			else {
				continue;
			}
		}
		if (items[j+1] != NULL) {
			parameters[counter] = malloc(sizeof(char)*2);
			strcpy(parameters[counter], "|");
			counter++;
			if (counter >= COMMAND_ARGV_MAX) {
				return -1;
			}
		}
		j++;
	}
	parameters[counter] = NULL;
	free(s);
	j=0;
	while (items[j] != NULL) {
		free(items[j]);
		items[j] = NULL;
		j++;
	}
	free(items);
	items = NULL;
	return 1;
	/*printf("counter:%d\n", counter);
	*for(j=0;j<counter;j++){
	*	write(1, parameters[j], strlen(parameters[j]));
	*	write(1, "\n", 1);
	*}
	*/
}
