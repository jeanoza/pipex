#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		printf("child\n");
	}
	else
	{
		waitpid(-1, &status, 0);
		printf("parent\n");
		exit(1);
	}
	printf("out");

	return (0);
}