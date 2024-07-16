/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:12:38 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/15 21:07:13 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
******************************************************************************/
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  </!>
///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************

			░█████╗░  ███████╗░█████╗░██╗██████╗░███████╗
			██╔══██╗  ██╔════╝██╔══██╗██║██╔══██╗██╔════╝
			███████║  █████╗░░███████║██║██████╔╝█████╗░░
			██╔══██║  ██╔══╝░░██╔══██║██║██╔══██╗██╔══╝░░
			██║░░██║  ██║░░░░░██║░░██║██║██║░░██║███████╗
			╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚══════╝



// readline library
// Management: Commands like history, !number, and !! can interact with the history
char *readline(const char *prompt);
void rl_clear_history(void);
int rl_on_new_line(void);
	> after handling signals or asynchronous events that affect the terminal
int rl_replace_line(const char *text, int clear_undo);
	> auto-completion
int rl_redisplay(void);
	> Redraws the prompt and input line.
int add_history(const char *string);

// unistd.h
int access(const char *pathname, int mode);

// sys/wait.h
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
pid_t wait3(int *wstatus, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);

// signal.h
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int kill(pid_t pid, int sig);

// unistd.h
char *getcwd(char *buf, size_t size);
int chdir(const char *path);

// sys/stat.h
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);

// unistd.h
int unlink(const char *pathname);
int dup(int oldfd);

// dirent.h
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

// unistd.h
int isatty(int fd);

// unistd.h
char *ttyname(int fd);
int ttyslot(void);

// sys/ioctl.h
int ioctl(int fd, unsigned long request, ...);

// stdlib.h
char *getenv(const char *name);

// termios.h
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int tcgetattr(int fd, struct termios *termios_p);

// termcap.h
int tgetent(char *bp, const char *name);
int tgetflag(char id[2]);
int tgetnum(char id[2]);
char *tgetstr(char id[2], char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));




command < input_file
command > output_file
command >> output_file
command << delimiter
&&
||



cd: Change directory with only a relative or absolute path.
echo: With option -n.
pwd: Print working directory with no options.
export: Handle environment variables with no options.
unset: Remove environment variables with no options.
env: Display environment variables with no options or arguments.
exit: Exit the shell with no options.


cd: Change directory.
exit: Terminate the shell.
echo: Print arguments to the standard output.
pwd: Print current working directory.
export: Set environment variables.
unset: Unset environment variables.
history: Display command history.
alias: Define or display aliases.
type: Display information about commands (alias, built-in, executable).
help: Display help information about built-in commands or shell features.



	waitpid(pid, &status, 0)
WIFEXITED(status): Returns true if the child terminated normally (by calling exit or returning from main).
WEXITSTATUS(status): Returns the exit status of the child. This should only be used if WIFEXITED(status) is true.
WIFSIGNALED(status): Returns true if the child process was terminated by a signal.
WTERMSIG(status): Returns the signal number that caused the child to terminate. This should only be used if WIFSIGNALED(status) is true.


BAD TEST
	echo -nnd salut
	E'C'HO
	echo a | grep a

	< !!! >		ccmd that start or end with && ||
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////]
int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		rtrn;

	initialization(ac, av, env, &data);
	while (1)
	{
		rtrn = ft_minishell(&data);
		if (WEXITSTATUS(rtrn) == 255)
			break ;
	}
	end(&data, 0);
	return (0);
}
