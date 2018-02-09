#include "simple_sh.h"

int builtin_pipe(char **history, char **item, int *h_counter)
{
	if (strcmp(item[0], "cd") == 0 || strcmp(item[0], "exit") == 0) {
		exit(0);
		return 1;
	}
	else if (strcmp(item[0], "history") == 0) {
		if (item[1] == NULL) {
			int i = 0;
			char a[3];
			while (history[i] != NULL) {
				sprintf(a, "%d", i);
				write(1, a, strlen(a));
				write(1, " ", 1);
				write(1, history[i], strlen(history[i]));
				write(1, "\n", 1);
				i++;
			}
			write(1, "aaaa", 4);
			exit(0);
			return 1;
		}
		else if (strcmp(item[1], "-c") == 0) {
			clear_history(history);
			*h_counter = 0;
			exit(0);
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}
	

