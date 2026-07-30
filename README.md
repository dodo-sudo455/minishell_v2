*This project has been created as part of the 42 curriculum by doyelee, minseobk.*

# minishell

## Description
Goal
- Write a simple UNIX shell programs similar to `bash`.

Overview
- `minishell` parses user commands, handles quotes and environment variables, and executes programs. It supports pipes, input/output redirections, and standard signals.

Key Features:
- Execution of commands via `PATH`.
- Pipes (`|`) and Redirections (`<`, `>`, `<<` heredoc, `>>`).
- Built-ins: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.
- Environment variable expansion (`$VAR`, `$?`).
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).

## Instructions
Compilation
```bash
make
```

Execution
```bash
./minishell
```

## Resources
Documentations
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- `man readline`

AI Usage
- Product: GitHub Copilot
- Purpose: boilerplate generation, debugging, testing
