#include "Header.h"

extern process_list * Head;
extern process_list * bg;
extern int pid;
extern int status;

void execute_internal_commands(char *input_string)
{
	// logic for squeezing the unnecessary space in input string
	int i=0;
	while(input_string[i] != '\0')
	{
		while(input_string[i]== ' ')
		{
			int k=i;
			if(input_string[k]==input_string[k+1])
			{
				while(input_string[k] != '\0')
				{
					input_string[k] = input_string[k+1];
					k++;
				}
				i=i-1;
			}
			i++;
		}
		i++;
	}
	if(strstr(input_string,"cd"))
	{
		chdir(input_string+3);// change directory system call
	}
	else if((strstr(input_string,"mkdir")))
	{
		mkdir(input_string+6,0777);// create directory system call
	}
	else if(!(strcmp(input_string,"pwd")))
	{
		printf("%s\n",getcwd(NULL,50));// To display present working directory
	}
	else if(!(strcmp(input_string,"exit")))
	{
		exit(0);
	}
	else if(!(strncmp(input_string,"echo",4)))// echo commands
	{
		if(!(strcmp(input_string,"echo $$")))
		{
			printf("%d\n",getpid());
		}
		else if(!(strcmp(input_string,"echo $?")))
		{
			int status;
			printf("%d\n",WEXITSTATUS(status));
		}
		else if(!(strcmp(input_string,"echo $SHELL")))
		{
			char * ptr = "SHELL";
			printf("%s\n",getenv(ptr));
		}
		else
		{
			printf("Wrong Input Format For echo Command\n");
		}
	}
	else if(!(strcmp(input_string,"jobs")))
	{
		if(Head)
		{
			print_list(Head);// displaying stopped processes
		}
		else
		{
			printf("No Current Stopped Process\n");
		}
	}
	else if(!(strcmp(input_string,"fg")))
	{
		printf("%s\n",Head -> process);
		pid = Head -> pid;
		kill(Head->pid,SIGCONT);// continuing the stopped process
		waitpid(Head->pid,&status,WUNTRACED);// wait untill process gets stopped or terminated
		Delete_first(&Head);// remove the job after task completion
	}
	else if(!(strcmp(input_string,"bg")))
	{
		signal(SIGCHLD,signal_handler);//registering the handler for sigchild signal
		bg = malloc(sizeof(bg));// separate struct to store the process running in background
		bg -> pid = Head -> pid;
		strcpy(bg -> process,Head -> process);
		printf("%s &\n",bg -> process);
		kill(Head->pid,SIGCONT);// continuing the stopped process
		Delete_first(&Head);// remove the job after task completion
	}
	else if(!(strcmp(input_string,"clear")))
	{
		system("clear");
	}
}
