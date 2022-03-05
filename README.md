# Pipex

## Resume

> Goal : imitate exactly `pipe` of terminal.
>
> hello

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

[pipex_tutorial](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
