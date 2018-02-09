#include "simple_sh.h"

int s2i(char *parameters)
{
	if (strcmp(parameters, "0") == 0) {
		return 0;
	}
	else {
		int i = atoi(parameters);
		if (i <= 0) {
			return -1;
		}
		else {
			return i;
		}
	}
}
