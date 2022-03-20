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

- Validation args

  ```c

  static void	validation_args(int ac, char **av)
  {
    //FIXME: version if i don't do multiple fork()
    if (ac != 5)
    {
      write(1, "usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 44);
      exit (EXIT_FAILURE);
    }
    if (*(av[2]) == 0 || *(av[3]) == 0)
    {
      write(1, "Error: cmds can't be empty string\n", 34);
      exit (EXIT_FAILURE);
    }

    //FIXME: version multiple fork()
    int	i;

    if (ac < 5)
    {
      write(1, "usage: ./pipex infile \"cmd1\" \"cmd2\" \"[cmd_n...]\" outfile\n", 57);
      exit (EXIT_FAILURE);
    }
    i = 2;
    while (i < ac - 1)
    {
      if (*(av[i]) == 0)
      {
        write(1, "Error: cmds can't be empty string\n", 34);
        exit (EXIT_FAILURE);
      }
      ++i;
    }
  }

  ```

- Variables in structure to use like "global"

  ```c

  /* */
  char  **paths;
  char  **cmds;
  int   pipe_fd[2];
  CMD(optionnel)


  ```

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
      printf("[Child1] : Hello, world ! pid=%d\n",getpid());
      exit(0);
    }
    pid2 = fork();
    if (pid2 == 0) {
      printf("[Child2] : Hello, world ! pid=%d\n",getpid());
      exit(0);
    }
    else {
      printf("[Parent]: Hello, world ! pid=%d\n", getpid());
      exit(0);
    }

    //output called : [Parent] -> [Child 1] -> [Child 2]....
    // [Parent]: Hello, world ! pid=81955
    // [Child1] : Hello, world ! pid=81956
    // [Child2] : Hello, world ! pid=81957
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

- `waitpid()`

  ```c
  /*
   * pid == -1: the call waits for any child process. (USE THIS in pipex)
   * pid == 0, the call waits for any child process in the process group of the caller.
   * pid > 0, the call waits for THE PROCESS with process id pid
   * pid < -1, the call waits for any process whose process GROUP id equals the absolute value of pid.
   */
  pid_t waitpid(pid_t pid, int *stat_loc, int options);



  ```

- `dup2()`

  ```c
  /*
   * close fildes2 and copy fd1 to fd2 location.
   * return: fd value if success, else -1
   */
  int dup2(int fildes, int fildes2);
  ```

- File Descriptor

  ```
                         -----------------
               0         |     stdin     |
                         -----------------
               1         |     stdout    |
                         -----------------
               2         |     stderr    |
                         -----------------
               3         |     infile    |  // open()
                         -----------------
               4         |     outfile   |  // open()
                         -----------------
               5         |     end[0]    |
                         -----------------
               6         |     end[1]    |
                         -----------------
  ```

  to

  ```
                         -----------------
               0         |     infile *  |  (x stdin closed)
                         -----------------
               1         |     end[1] *  |  (x stdout closed)
                         -----------------
               2         |     stderr    |
                         -----------------
               3         |     infile    |
                         -----------------
               4         |     outfile   |
                         -----------------
               5         |     end[0]    |
                         -----------------
               6         |     end[1]    |
                         -----------------            *duplicated
  ```

### etc...

- Args

  > - av[1] = input path(stdin)
  > - av[2] = cmd1
  > - av[3] = cmd2
  > - av[4] = output path(stdout)

  <br/>

- Redirection

  > - stdout
  >
  >   - `> _FILE_PATH` :
  >     - if no file => create
  >     - else => override
  >   - `>> _FILE_PATH` :
  >     - if no file => create
  >     - else => add at the finish line
  >
  > - stdin
  >   - `< _FILE_PATH` :
  >     - if no file => Error (ex: zsh: no such file or directory: \_FILE_PATH)
  >     - else => read this.\_FILE_PATH
  >   - `<< _LIMITER` : write `heredoc>`(here document), until `this._LIMITER` called
  >
  > <br/>cf: `write "Hello world!" and "Bonjour a tous!" then save in 'output'`

  ```bash
  <<END cat > output

  heredoc> Hello world!
  heredoc> Bonjour a tous!
  heredoc> END

  ```

- variable env
  ```c
  int main(int ac, char **av, char **env)
  {
    (void)ac;
    (void)av;
    int	i;
    i = 0;
    while (env && env[i])
    {
      printf("env[%d]:%s\n", i, env[i]);
      ++i;
    }
    return (0);
  }
  /*
  env[0]:TERM_PROGRAM=vscode
  env[1]:_P9K_TTY=/dev/ttys001
  env[2]:TERM=xterm-256color
  env[3]:SHELL=/bin/zsh
  env[4]:TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n0004yww0017q7/T/
  env[5]:Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.I8RG0ULyuK/Render
  env[6]:TERM_PROGRAM_VERSION=1.63.2
  env[7]:TERM_SESSION_ID=w0t0p0:5859BD2F-32C5-4656-BAE5-9F7C7A7EDDEC
  env[8]:ZSH=/Users/kychoi/.oh-my-zsh
  env[9]:USER=kychoi
  env[10]:SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.OF6Xd2rUot/Listeners
  env[11]:__CF_USER_TEXT_ENCODING=0x9EE7:0x0:0x0
  env[12]:PAGER=less
  env[13]:LSCOLORS=Gxfxcxdxbxegedabagacad
  env[14]:PATH=/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki
  env[15]:PWD=/Users/kychoi/Documents/pipex
  env[16]:P9K_SSH=0
  env[17]:P9K_TTY=old
  env[18]:LANG=en_US.UTF-8
  env[19]:ITERM_PROFILE=Default
  env[20]:XPC_FLAGS=0x0
  env[21]:XPC_SERVICE_NAME=0
  env[22]:SHLVL=3
  env[23]:HOME=/Users/kychoi
  env[24]:COLORFGBG=7;0
  env[25]:LC_TERMINAL_VERSION=3.4.2
  env[26]:ITERM_SESSION_ID=w0t0p0:5859BD2F-32C5-4656-BAE5-9F7C7A7EDDEC
  env[27]:LESS=-R
  env[28]:LOGNAME=kychoi
  env[29]:LC_TERMINAL=iTerm2
  env[30]:DISPLAY=/private/tmp/com.apple.launchd.n13OzKa5Jd/org.macosforge.xquartz:0
  env[31]:COLORTERM=truecolor
  env[32]:APPLICATION_INSIGHTS_NO_DIAGNOSTIC_CHANNEL=true
  env[33]:ORIGINAL_XDG_CURRENT_DESKTOP=undefined
  env[34]:VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n0004yww0017q7/T/vscode-git-775b965e9d.sock
  env[35]:GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
  env[36]:VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/MacOS/Electron
  env[37]:VSCODE_GIT_ASKPASS_EXTRA_ARGS=--ms-enable-electron-run-as-node
  env[38]:VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
  env[39]:OLDPWD=/Users/kychoi/Documents/pipex
  env[40]:_=/Users/kychoi/Documents/pipex/./pipex
  */
  ```

### References:

- [pipex-tutorial-42](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
