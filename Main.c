/* Name        : Siva Kumar P
   Date        : 12/02/2026
   Description : Developed a simplified Linux shell in C that supports execution of external commands, built-in commands,
  		 background processes, pipelines, and signal handling. The shell parses user input, creates child processes 
		 using fork(), executes programs using exec(), and manages process synchronization using waitpid(). 

                 Core Concept : 
		 		-> Fork–Exec process model
				-> Process synchronization (wait, waitpid)
				-> Signal handling (SIGINT, SIGCHLD)
				-> Command parsing and tokenization
				-> File descriptor manipulation (pipes, redirection)
				-> Built-in command execution within parent process

                 Key Advantages :
                                ->Strong understanding of Linux internals
                                ->Hands-on systems programming experience
                                ->Demonstrates process control & IPC knowledge
                                ->Directly relevant to Embedded/Linux roles
*/
#include"Header.h"
// Declaring variables and Arrays with global scope to access from all files
char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "clear","pushd", "popd", "dirs", "let", "eval",
	"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
	"exit", "mkdir", "exec", "shopt", "caller", "true", "type", "hash", "fg", "bg", "jobs", "bind", "help", NULL};

char * external_commands[153];
int pid = 0;
int status = 0;
char Prompt_string[20] = "MINISHELL";
char Input_string[50];
process_list * Head = NULL;
process_list * bg = NULL;
int main()
{
	system("clear");
	extract_external_commands(external_commands);//To make a 2d array of external command from the .txt file
	scan_input(Prompt_string,Input_string);
}
