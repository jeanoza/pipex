# Pipex

## Resume

### Goal : imitate exactly `pipe` of terminal.

### Library && Function autorized

```c
/* unistd.h */
int		close(int fildes);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int		access(const char *path, int mode);
int		dup(int fildes);
int		dup2(int fildes, int fildes2);
int		execve(const char *path, char *const argv[], char *const envp[]);
pid_t	fork(void); // create new process
int		pipe(int fildes[2]);
int		unlink(const char *path);

/* sys/wait.h */
pid_t	wait(int *stat_loc);
pid_t	waitpid(pid_t pid, int *stat_loc, int options);

/* fcntl.h */
int		open(const char *path, int oflag, ...);

/* stdlib.h */
int		malloc(size_t size);
void	free(void *ptr);
void	exit(int status);

/* stdio.h */
void	perror(const char *s);

/* string.h */
char *strerror(int errnum);

```


### Theory

  - Basic Structure

    ```txt
        infile                                             outfile
    as stdin for cmd1                                 as stdout for cmd2
          |                        PIPE                        ↑
          |           |---------------------------|            |
          ↓             |                       |              |
          cmd1   -->    end[1]       ↔       end[0]   -->     cmd2
                        |                       |
                cmd1   |---------------------------|  end[0]
              output                             reads end[1]
            is written                          and sends cmd1
              to end[1]                          output to cmd2
          (end[1] becomes                      (end[0] becomes
            cmd1 stdout)                           cmd2 stdin)

    ```

- Args

  > - av[1] = input path(stdin)
  > - av[2] = cmd1
  > - av[3] = cmd2
  > - av[4] = output path(stdout)

<br/>

- Environ variable print

  ```c

  int main(void)
  {
  	char **ptr;
  	extern char **environ;k

  	ptr = environ;
  	while (*ptr != 0)
  	{
  	printf("ptr:%s\n", *ptr);
  	++ptr;
  	}
  }

  ```

- FORK && PID Example

  ```c
  //one child && one parent
  int main()
  {
  	int pid;
  	pid = fork();
  	if(pid ==0)
  		printf("[Child] : Hello, world pid=%d\n",getpid());
  	else
  		printf("[Parent] : Hello, world pid=%d\n",getpid());

  	//output called : [Parent] -> [Child]
  	//[Parent] : Hello, world pid=72176
  	//[Child] : Hello, world pid=72192
  }

  //multiple children
  int main()
  {
  	int pid1, pid2;
  	pid1 = fork();
  	if (pid1 == 0) {
  		printf("[Child 1] : Hello, world ! pid=%d\n",getpid());
  		exit(0);
  	}
  	pid2 = fork();
  	if (pid2 == 0) {
  		printf("[Child 2] : Hello, world ! pid=%d\n",getpid());
  		exit(0);
  	}
  	else {
  		printf("[Parent]: Hello, world ! pid=%d\n", getpid());
  		exit(0);
  	}

  	//output called : [Parent] -> [Child 1] -> [Child 2]....
  	// [Parent]: Hello, world ! pid=81955
  	// [Child 1] : Hello, world ! pid=81956
  	// [Child 2] : Hello, world ! pid=81957
  }

  //fork wait
  int main(void)
  {
    int pid, child, status;
    
    printf("[%d] Parent start\n", getpid());
    pid = fork();
    if (pid == 0)
    {
      printf("[%d] Child start\n", getpid());
      exit(1);
    }

    child = wait(&status);
    printf("[%d] Child[%d(status:%d)] end\n", getpid(), child, status);
    printf("\tCode exit:%d\n", status >> 8);
  }
  //[76677] Parent start
  //[76678] Child start
  //[76677] Child[76678(status:256)] end
  //        Code exit:1
  ```

### To verify

- Difference between `>>` and `>`, `<<` and `<` ?
- Redirection
	>- stdout
	>	- `> _FILE_PATH` :
	>		- if no file => create
	>		- else => override
	>	- `>> _FILE_PATH` :
	>		- if no file => create
	>		- else => add at the finish line
  >
	>- stdin
	>	- `< _FILE_PATH` :
	>		- if no file => Error (ex: zsh: no such file or directory: _FILE_PATH)
	>		- else => read this._FILE_PATH
	>	- `<< _KEYWORD` : write until this._KEYWORD called
  >
  <br/>cf: `write hello world\nbonjour a tous && save in 'output'`
    ```bash
    <<\END cat > output

    heredoc> Hello world!
    heredoc> Bonjour a tous!
    heredoc> END

    ```

		


### References:

- [pipex-tutorial-42](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
