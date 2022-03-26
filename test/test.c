#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	int pid;
	int status;
	int i;

	i = 0;
	printf("start getpid():%d\n", getpid());
	for (i = 0; i < 10;++i)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("child getpid():%d - i:%d\n", getpid(), i);
			exit(1);
		}
		if (pid > 0)
		{
			waitpid(-1, &status, 0);
			// wait(NULL);
			printf("(status:%d)parent pid:%d getpid():%d - i:%d\n", status, pid, getpid(), i);

		}
	}
	printf("out");

	return (0);
}