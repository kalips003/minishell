# minishell

## Description
`minishell` is a 42 project that consists in creating a simplified Unix shell in C.

The goal is to understand how a real shell works by implementing command parsing, execution, environment handling, and process management.

The shell supports basic command execution, pipes, redirections, and built-in commands.

---

## Features

- Command execution using `execve`
- PATH resolution
- Environment variable management
- Pipes (`|`)
- Redirections:
  - `<` input
  - `>` output
  - `>>` append
  - `<<` heredoc
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Extra
  - handling of any depth wildcards: `echo */*/*`
  - support -e: `./minishell -e <cmd>`

---

## Usage

```bash
make a # compile and run the minishell
make m # run all tests in the data/TESTS file and compare the output to the bash --posix output
```