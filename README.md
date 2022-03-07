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

### To verify

- Difference between `>>` and `>`, `<<` and `<` ?

- stdout
  - `> _FILE_PATH` :
    - if file exist -> override
    - if no file -> create
  - `>> _FILE_PATH` :
    - if file exist -> add at the finish line
    - if no file -> create
- stdin
  - `< _FILE_PATH`

### References:

- [pipex-tutorial-42](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
