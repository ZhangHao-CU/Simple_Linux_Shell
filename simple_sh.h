#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include <errno.h>

#define COMMAND_ARGV_MAX 10
#define HISTORY_LIST_MAX 100
#define BUFFER_MAX 1024

void prompt();
int interpret_input(char *buf, char **parameters);
void run();
void add_history(int *counter, char **history, char *command);
int built_in(int *h_counter, char **history, char **parameters, int pipe, char **temp);
int s2i(char *parameter);
void clear_history(char **history);
void generate_pipe(char *line, int count_loop, char **history, int *h_counter);
int interpret_line(char *line, char *delimtor, char **items);
int builtin_pipe(char **history, char **item, int *h_counter);
