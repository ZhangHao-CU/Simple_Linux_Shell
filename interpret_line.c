#include "simple_sh.h"

int interpret_line(char *line, char *delimtor, char **items)
{
	int i = 0;
	while (items[i] != NULL) {
		free(items[i]);
		items[i] = NULL;
		i++;
	}
	char *s = strdup(line);
	char *name;
	i=0;
	while (1) {
		name = strsep(&s, delimtor);
		if (name != NULL) {
			if (strcmp(name,"\0") != 0) { /*get rid of delimtor*/
				items[i] = malloc(sizeof(char)*(strlen(name)+1));
				strcpy(items[i], name);
				i++;
			}
			else {
				continue;
			}
		}
		else {
			break;	
		}
	}
	free(s);
	return i;
}
