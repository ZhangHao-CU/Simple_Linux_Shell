#include "simple_sh.h"
#define TRUE 1

int pipe_flag;

void generate_pipe(char *line, int count_loop, char **history, int *h_counter)
{
	int fd[2];
	pipe(fd);
	char *items[COMMAND_ARGV_MAX];
	char *item[COMMAND_ARGV_MAX];
	int i = 0;
	for (i=0; i < COMMAND_ARGV_MAX; i++) {
		items[i] = NULL;
		item[i] = NULL;
	}
	count_loop++;
	pid_t child_id = fork();
	if (child_id == -1) {
		write(1, "error:fork failed!\n", 19);
		return;
	}
	if (child_id == 0) { /*child process*/
	
		dup2(fd[1], 1);
		close(fd[0]);
		interpret_line(line, "|", items);
		interpret_line(items[count_loop-1], " ", item);
		if (builtin_pipe(history, item, h_counter) == 0) {
			if (execve(item[0], item, 0) == -1) {
					fprintf(stderr, "error:%s\n", strerror(errno));
			}
			exit(1);
		}
	}
	else { /*father process*/
	
		dup2(fd[0], 0);
		close(fd[1]);
		if (pipe_flag > count_loop) {
			//printf("1\n");
			generate_pipe(line,count_loop,history, h_counter);
		}
		else{
			interpret_line(line, "|", items);
			interpret_line(items[count_loop], " ", item);
			if (builtin_pipe(history, item, h_counter) == 0) {
				if (execve(item[0], item, 0) == -1) {
					fprintf(stderr, "error:%s\n", strerror(errno));
				}
			}		
			waitpid(-1,0,0);
		}
	}
}
void run()
{
	int status, i;
	/*indicate that whether need to read from stdin*/
	int flag = 0;
	int built_result; 
	char *path;
	char **parameters;
	char **history_list;
	char **temp;
	int history_counter = 0;
	int length;
	char buffer[BUFFER_MAX];
	char buf[BUFFER_MAX];
	int offset;

	parameters = malloc(sizeof(char *)*COMMAND_ARGV_MAX);
	history_list = malloc(sizeof(char *)*HISTORY_LIST_MAX);
	temp = malloc(sizeof(char *)*COMMAND_ARGV_MAX);
	for(i=0; i < COMMAND_ARGV_MAX; i++){
		parameters[i] = NULL;
		temp[i] = NULL;
	}
	for (i=0; i < HISTORY_LIST_MAX; i++) {
		history_list[i] = NULL;
	}

	while (TRUE) {
		if(flag == 0){
			prompt();
			length = read(0, buffer, BUFFER_MAX);
			if(length == 1){
				write(1, "error:no commands!\n", 19);
				continue;
			}
			memset(buf, '\0', sizeof(buf));
			strncpy(buf, buffer, length-1);
			if (interpret_input(buf, parameters) == -1) {
				write(1, "error:Too much parameters\n", 26);
				continue;
			}
			add_history(&history_counter, history_list, buf);

		}
		else {	
			if (pipe_flag > 0) {
				memset(buffer, '\0', sizeof(buffer));
				strcpy(buffer, strstr(buf, "|"));
				memset(buf, '\0', sizeof(buf));
				strcpy(buf, history_list[offset]);
				strcat(buf, buffer);
			}
			else {
				memset(buf, '\0', sizeof(buf));
				strcpy(buf, history_list[0]);
			}
			if (interpret_input(buf, parameters) == -1) {
				write(1, "error:Too much parameters\n", 26);
				continue;
			}
			flag =0;
		}
		/*calculate pipe_flag*/
		i = 0;
		pipe_flag = 0;
		while (parameters[i] != NULL) {
			if (strcmp(parameters[i], "|") == 0) {
				pipe_flag++;
			}
		/*	write(1, parameters[i], strlen(parameters[i]));
		*	write(1, "\n", 1);
		*/
			i++;
		}
		/*printf("pipe_flag = %d\n", pipe_flag);*/
		if (parameters[1] != NULL) {
			offset = s2i(parameters[1]);
		}
		if (pipe_flag == 0) {
			built_result=built_in(&history_counter, history_list, parameters, pipe_flag, temp);
		}
		else {
			i = 0;
			while (strcmp(parameters[i], "|") != 0) {
				temp[i] = malloc(sizeof(char)*(strlen(parameters[i])+1));
				strcpy(temp[i], parameters[i]);
				i++;
			}
			temp[i] = NULL;
			built_result = built_in(&history_counter, history_list, temp, pipe_flag, temp);
		}
		switch (built_result) {
		case 0:
			/*	printf("history [] command\n");*/
				flag = 1;
				continue;
		case 1:
			/*	printf("built-in command!\n");*/
				continue;
		case 2:
			/*	printf("arguements error\n");*/
				write(1, "error:Wrong arguements for builtin commands!\n", 45);
				continue;
		case 3:
			/*	printf("normal command\n");*/
				break;
		default:
				break;
		}
		path = malloc(sizeof(char)*(strlen(parameters[0])+1));
		strcpy(path, parameters[0]);
		/*fork a child process to execute the instructions*/
		pid_t child_id = fork();
		if (child_id < 0) {
			write(1, "error:fork failed\n", 18);
			continue;
		}
		if(child_id != 0){
			waitpid(-1, &status, 0);
		}
		else{
			if (pipe_flag > 0) {	
				generate_pipe(buf, 0, history_list, &history_counter);
				exit(0);
			}
			else{
			
				if (execve(parameters[0], parameters, 0) == -1) {
					fprintf(stderr, "error:%s\n", strerror(errno));
					exit(1);
				}
			}
		}
	}
}



int main(int argc, char *argv[])
{
	run();
	return 0;
}
