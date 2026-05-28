#include "Header.h"

int execute_external_commands(char *input_string)
{
	char temp[50];
	strcpy(temp,input_string);
	char * args[50];
	int i=0;
	args[i] = strtok(temp," ");//strtok function to split the input string as 2d array
	while(args[i])
	{
		i++;
		args[i] = strtok(NULL," ");
	}
	int flag = 0;
	for(int j=0;j<i;j++)
	{
		if(!(strcmp(args[j],"|")))
		{
			if(!(args[j+1]))
			{
				printf("Wrong Input Format for Pipe\n");
				exit(0);
				return 0;
			}
			else if(!(strcmp(args[j+1],"|")))
			{
				printf("Wrong Usage of Pipe\n");
				exit(0);
				return 0;
			}
			else
			{
				flag = 1;
			}
			break;
		}
	}
	if(flag == 0)
	{
		execvp(args[0],args);
	}
	else
	{
		int pipe_pos[i];
		int pos = 0;
		pipe_pos[pos] = 0;
		for(int k=0;k<i;k++)
		{
			if(!(strcmp(args[k],"|")))//check for '|'
			{
				args[k] = NULL;
				pos++;
				pipe_pos[pos] = k+1;
			}
		}
		// creation of the pipe
		int pipefd[2];
		int Stdin = dup(0);
		for(int l=0;l<=pos;l++)
		{
			if(l != pos)
			{
				if(pipe(pipefd) == -1)
				{
					perror("pipe");
					return -1;
				}
			}
			//printf("%d %d\n",pipefd[0],pipefd[1]);
			//creating a child process
			pid_t c1 = fork();
			if(c1 > 0)//parent
			{
				if(l != pos)
				{
					//redirecting input
					dup2(pipefd[0],0);
					//close unused pipe ends
					close(pipefd[0]);
					close(pipefd[1]);
				}
				wait(NULL);
			}
			else if(c1 == 0)//child 1
			{
				int Stdout = dup(1);
				if(l != pos)
				{
					dup2(pipefd[1],1); // redirecting the output to pipe
							   //close the unused pipe end
					close(pipefd[0]);
				}
				execvp(args[(pipe_pos[l])],(args+pipe_pos[l]));
				dup2(Stdout,1);// redirecting the output to stdout to print error message
				printf("ERROR : '%s' No Such Command Exist\n",args[pipe_pos[l]]);
				exit(0);
			}
		}
		dup2(Stdin,0);
	}
	exit(0);// close the called process to execute the command
}
