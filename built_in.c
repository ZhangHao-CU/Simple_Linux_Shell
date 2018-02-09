#include "simple_sh.h"
/*This function run the built-in command lines. As for return values, 0 represents executing one of the historical commands, 1 means successfully run a built-in command, 2 represents some errors, 3 represents normal commands*/


int built_in(int *h_counter, char **history, char **parameters, int pipe, char **temp)
{
	int i;
	int offset;
	if (strcmp(parameters[0], "exit") == 0 && pipe == 0) {
		i = 0;
		for (i=0; i < COMMAND_ARGV_MAX; i++) {
			if (parameters[i] != NULL) {
				free(parameters[i]);
			}
			if (temp[i] != NULL) {
				free(temp[i]);
			}
			i++;
		}
		for (i=0; i < HISTORY_LIST_MAX; i++) {
			if (history[i] != NULL) {
				free(history[i]);
			}
			i++;
		}
		free(history);
		free(parameters);
		free(temp);
		exit(0);
	}
	else if (strcmp(parameters[0], "cd") == 0 && pipe == 0) {
		if (chdir(parameters[1]) == -1) {
			printf("error:No such file or directory\n");
		}
		return 1;
	}
	if (strcmp(parameters[0], "history") == 0) {
		if (parameters[1] == NULL && pipe == 0) {
			i = 0;
			char a[3];
			while (history[i] != NULL) {
				sprintf(a, "%d", i);
				write(1, a, strlen(a));
				write(1, " ", 1);
				write(1, history[i], strlen(history[i]));
				write(1, "\n", 1);
				i++;
			}
			return 1;
		}
		else if (parameters[2] == NULL && parameters[1] != NULL) {
			if (strcmp(parameters[1], "-c") == 0 && pipe == 0) {
				clear_history(history);
				*h_counter = 0;
				return 1;
			}
			else if (strcmp(parameters[1], "-c") != 0) {
				if ((offset = s2i(parameters[1])) != -1) {
					if (history[offset] != NULL) {
						interpret_input(history[offset], parameters);
						return 0;
					}
					else{
						return 2;
					}
					/*return execute_history(history[offset], parameters); //return 0 or 2*/
				}
				else{
					return 2;
				}
			}
			else {
				return 3;
			}
		}
		else{
			return 3;
		}
	}
	else {
		return 3;
	}
}
