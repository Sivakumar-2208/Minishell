#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  	3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//structure to store the stopped process details
typedef struct node
{
	int pid;
	char process[50];
	struct node * link;
}process_list;

//Functions to Run a minishell
void scan_input(char *Prompt_string,char *Input_string);
char *get_command(char *Input_string);
int check_command_type(char *command);
void echo(char *input_string, int status);
int execute_external_commands(char *input_string);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);
int Delete_first(process_list ** head);
int Insert_first(struct node ** head,char * str,int pid);
void print_list(process_list * head);

#endif
