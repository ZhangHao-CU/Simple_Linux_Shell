#include "simple_sh.h"

const int HOSTNAME_MAX = 255;
const int PATHNAME_MAX = 1023;

void prompt()
{
/*	struct passwd *usr = NULL;
*	char hostname[HOSTNAME_MAX];
*	char pathname[PATHNAME_MAX];
*	usr = getpwuid(getuid());
*	getcwd(pathname, PATHNAME_MAX);
*	if(gethostname(hostname, HOSTNAME_MAX)==0){
*		write(1, usr->pw_name, strlen(usr->pw_name));
*		write(1, "@", 1);
*		write(1, hostname, strlen(hostname));
*		//printf("%s@%s:", usr->pw_name, hostname);
*	}
*	else{
*		strcpy(hostname,"unknown host");
*		write(1, usr->pw_name, strlen(usr->pw_name));
*		write(1, "@", 1);
*		write(1, hostname, strlen(hostname));
*		//printf("%s@%s:", usr->pw_name, hostname);
*	}
*	write(1, pathname, strlen(pathname));
*/
	write(1, "$", 1);
	return;
}
