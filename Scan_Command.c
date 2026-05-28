#include "Header.h"

extern char * external_commands[];
extern int pid,status;

void scan_input(char *Prompt_string,char *Input_string)
{
	while(1)//Never ending loop for taking input till user wants to exit
	{
		signal(SIGINT,signal_handler);//Registering a own handler for sigint and sigtstp signals
		signal(SIGTSTP,signal_handler);
		pid = 0;
		printf("%s:~$ ",Prompt_string);
		memset(Input_string,0,sizeof(Input_string));//To make the Input string empty after each command execution
		scanf("%[^\n]",Input_string);
		getchar();
		if(Input_string[0] == '\0')
		{
			continue;
		}
		if(strstr(Input_string,"PS1="))
		{
			if(strlen(Input_string) >= 5)
			{
				if(!(strchr(Input_string,' ')))
				{
					strcpy(Prompt_string,Input_string+4);
				}
				else
				{
					printf("ERROR : Wrong Input For 'PS1=' Command !!\n");
				}
			}
			else
			{
				printf("ERROR : Wrong Input For 'PS1=' Command !!\n");
			}
			continue;
		}
		char * command = get_command(Input_string);//extract the command from input string without options
		int ret = check_command_type(command);//search for the command in both build in and external commands array
		switch(ret)
		{
			case BUILTIN:
				execute_internal_commands(Input_string);//Builtin commands definitions
				break;
			case EXTERNAL:
				pid = fork();// external commands are executed by chils process
				if(pid > 0)
				{
					waitpid(-1,&status,WUNTRACED);
				}
				else if(pid == 0)
				{
					signal(SIGINT,SIG_DFL);//Restoring the behaviour of sigint & sigtstp while command execution
					signal(SIGTSTP,SIG_DFL);
					execute_external_commands(Input_string);//External commands Execution
				}
				break;
			case NO_COMMAND:
				printf("Command not found\n");
				break;
		}
	}
}
