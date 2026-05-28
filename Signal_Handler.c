#include "Header.h"

extern char * builtins[];
extern char * external_commands[];
extern int pid;
extern int status;
extern char Prompt_string[];
extern char Input_string[];
extern process_list * Head;
extern process_list * bg;

void signal_handler(int sig_num)
{
	if(sig_num == SIGINT)// when sigint signal occured
	{
		if(pid == 0)// no process is executing currently
		{
			printf("\n%s:~$ ",Prompt_string);
			fflush(stdout);
		}
		else// process is executing
		{
			printf("\n");
		}
	}
	else if(sig_num == SIGTSTP)// when sigtstp signal occured
	{
		if(pid == 0)// no process is executing
		{
			printf("\n%s:~$ ",Prompt_string);
			fflush(stdout);
		}
		else// process is executing
		{
			if(!(strcmp(Input_string,"fg")))
			{
				Insert_first(&Head,Head -> process,pid);// store the stopped process details in linked list
			}
			else
			{
				Insert_first(&Head,Input_string,pid);// store the stopped process details in linked list
			}
			printf("\nStopped \t %s\n",Head -> process);
		}
	}
	else if(sig_num == SIGCHLD)//when sigchld signal occured
	{
		int PID;
		PID = waitpid(-1,&status,WNOHANG);
		if(PID == bg -> pid)// check if terminated process is continued by Bg command 
		{
			if(WIFEXITED(status))// check if terminated
			{
				printf("Done \t %s\n",bg -> process);
				signal(SIGCHLD,SIG_DFL);// restoring sigchld behaviour
				scan_input(Prompt_string,Input_string);
			}
		}
	}
}
