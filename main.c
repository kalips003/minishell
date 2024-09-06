/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:12:38 by kalipso           #+#    #+#             */
/*   Updated: 2024/09/04 11:52:06 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

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


^C retour a la ligne? "sleep 255 | sleep 255 | sleep 255"
check for return values after using a signal : 130 for sigint and 131 for sigquit (use globalvariable g_signalreceived)

tests that break minishell:

echo -nnnnnnnnnnnnnnnnnnnnnnnn""



leak fd /dev/pts/1 -> ls
unset PWD then pwd -> invalid free?
echo ewkofwf > /dev/full -> no error message and wrong exit code



// dirent.h
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

for * wildcard






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


WIFEXITED(status):
    This macro checks if the child process terminated normally (i.e., by calling exit() or returning from main).
    Returns a non-zero value (true) if the child terminated normally.
WEXITSTATUS(status):
    This macro retrieves the exit status of the child if WIFEXITED(status) is true.
    It extracts the low-order 8 bits (i.e., the least significant byte) of the status, which is the actual exit code passed by the child process using exit() or returned from main.
WIFSIGNALED(status):
    This macro checks if the child process terminated due to a signal (i.e., if it was killed by a signal).
    Returns a non-zero value if the child process was terminated by a signal.
WTERMSIG(status):
    If WIFSIGNALED(status) is true, this macro retrieves the signal number that caused the child process to terminate.
WIFSTOPPED(status):
    This macro checks if the child process is currently stopped (not terminated) because it received a signal that stopped it.
    Returns a non-zero value if the child process is stopped.
WSTOPSIG(status):
    If WIFSTOPPED(status) is true, this macro retrieves the signal number that caused the child process to stop.
WIFCONTINUED(status):
    This macro checks if the child process was resumed after being stopped (only relevant in certain systems).
    Returns a non-zero value if the child process has been resumed by SIGCONT.


0x112233ff
| < > & $ ` " ' \ ; * ? [ ] { } ( ) ! # << >> <<< \001 \002

/: Directory separator.
": Encloses a string with variable expansion.
': Encloses a literal string with no expansion.
\\: Escapes the following character.
;: Separates commands.
*: Wildcard for matching multiple characters.
?: Wildcard for matching a single character.
[ ]: Used in pattern matching and file tests.
{ }: Brace expansion.
`: Command substitution (deprecated in favor of $()).
$(): Modern command substitution.
!: History expansion.
#: Comment.
>: Redirect output (overwrite).
>>: Redirect output (append).
<: Redirect input.
&: Background process.
&&: Conditional execution (if successful).
||: Conditional execution (if failed).
(): Group commands.
|&: Pipe both stdout and stderr.
<<: Here document.
<<<: Here string.


STOCKER TOUT LES PID QQ PART, PROBABLEMEBT DAND LA GLOBALE
LES REUTILISER POUR SIGkill
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////]
// int	g_signalreceived;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	initialization(ac, av, env, &data);
	while (1)
		ft_minishell(&data);
	end(&data, 0);
	return (0);
}


// 				SIGNALS
/*
struct sigaction {
	sa_handler (*func) SIG_DFL; SIG_IGN; void handler(int signum);
	sa_sigaction (*func) void handler(int signum, siginfo_t *info, void *context)
	sa_mask:	what signals to ignore while handler is running
	sa_flags: Flags that modify the behavior of the signal handling.
			SA_RESTART; SA_NOCLDSTOP; SA_SIGINFO; SA_ONSTACK;
}







		0	???
SIGHUP	1	Hangup detected on controlling terminal or death of controlling process	N/A
SIGINT	2	Interrupt from keyboard	Ctrl + C
SIGQUIT	3	Quit from keyboard	Ctrl + \
SIGILL	4	Illegal Instruction	N/A
SIGTRAP	5	Trace/breakpoint trap	N/A
SIGABRT	6	Abort signal from abort	N/A
SIGBUS	7	Bus error (bad memory access)	N/A
SIGFPE	8	Floating-point exception	N/A
SIGKILL	9	Kill signal (cannot be caught or ignored)	N/A
SIGUSR1	10	User-defined signal 1	N/A
SIGSEGV	11	Segmentation fault	N/A
SIGUSR2	12	User-defined signal 2	N/A
SIGPIPE	13	Broken pipe: write to pipe with no readers	N/A
SIGALRM	14	Timer signal from alarm	N/A
SIGTERM	15	Termination signal	N/A
SIGSTKFLT	16	Stack fault on coprocessor	N/A
SIGCHLD	17	Child stopped or terminated	N/A
SIGCONT	18	Continue if stopped	N/A
SIGSTOP	19	Stop process	N/A
SIGTSTP	20	Stop typed at terminal	Ctrl + Z
SIGTTIN	21	Terminal input for background process	N/A
SIGTTOU	22	Terminal output for background process	N/A
SIGURG	23	Urgent condition on socket	N/A
SIGXCPU	24	CPU time limit exceeded	N/A
SIGXFSZ	25	File size limit exceeded	N/A
SIGVTALRM	26	Virtual alarm clock	N/A
SIGPROF	27	Profiling timer expired	N/A
SIGWINCH	28	Window resize signal	N/A
SIGIO	29	I/O now possible	N/A
SIGPWR	30	Power failure	N/A
SIGSYS	31	Bad system call	N/A

*/