#include "Header.h"
extern char * builtins[];
extern char * external_commands[];
extern int pid;
extern char Prompt_string[];
extern char Input_string[];

void extract_external_commands(char **external_commands)
{
	FILE * fd = fopen("External_Commands.txt","r");
	for(int i=0;i<152;i++)
	{
		char buff[50];
		fscanf(fd,"%[^\n]\n",buff);
		int len = strlen(buff);
		buff[len] = '\0';
		external_commands[i] = malloc(len+1);//storing the heap address of commands into 2d array
		strcpy(external_commands[i],buff);// copy the string from external .txt file to heap memory
	}
	external_commands[152] = NULL;
}

char *get_command(char *Input_string)
{
	int len = strlen(Input_string);
	char * command = malloc(len);// creating a string in heap to access from all files
	strcpy(command,Input_string);
	int i=0;
	while(command[i] != '\0')
	{
		if(command[i] == ' ')
		{
			command[i] = '\0';// Modifying the newly created string
			break;
		}
		i++;
	}
	return command;	
}

int check_command_type(char *command)
{
	// search for command is present or not
	int i = 0;
	while(builtins[i] != NULL)
	{
		if(!(strcmp(builtins[i],command)))
		{
			return BUILTIN;
		}
		i++;
	}
	int j = 0;
	while(external_commands[j] != NULL)
	{
		if(!(strcmp(external_commands[j],command)))
		{
			return EXTERNAL;
		}
		j++;
	}
	return NO_COMMAND;
}

int Insert_first(process_list ** head,char * str,int pid)
{
	// inserting the details of stopped proccess into linked list 
	process_list * new =malloc(sizeof(process_list));
	if(new == NULL)
	{
		return 0;
	}
	new -> pid = pid;
	strcpy(new -> process,str);
	new -> link = *head;
	*head = new;
	return 1;
}

int Delete_first(process_list ** head)
{
	// removing details of finished process which was once stopped
	if(*head == NULL)
	{
		return 0;
	}
	process_list * temp = *head;
	*head = (*head)->link;
	free(temp);
	return 1;
}

void print_list(process_list * head)
{
	int i = 1;
	while (head)// just display the details
	{
		printf("[%d] Stopped \t %s\n",i,head -> process);
		head = head -> link;
		i++;
	}
}
