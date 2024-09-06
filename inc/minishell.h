/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:43 by marvin            #+#    #+#             */
/*   Updated: 2024/09/04 05:30:43 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <pthread.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
// # include <termcap.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <time.h>
# include <sys/types.h>

# include "libft.h"

///////////////////////////////////////////////////////////////////////////////]
//
//			▒█▀▄▀█ ░█▀▀█ ▒█▄░▒█ ▒█▀▀▄ ░█▀▀█ ▀▀█▀▀ ▒█▀▀▀█ ▒█▀▀█ ▒█░░▒█
//			▒█▒█▒█ ▒█▄▄█ ▒█▒█▒█ ▒█░▒█ ▒█▄▄█ ░▒█░░ ▒█░░▒█ ▒█▄▄▀ ▒█▄▄▄█
//			▒█░░▒█ ▒█░▒█ ▒█░░▀█ ▒█▄▄▀ ▒█░▒█ ░▒█░░ ▒█▄▄▄█ ▒█░▒█ ░░▒█░░
//
///////////////////////////////////////////////////////////////////////////////]

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data			t_data;
typedef struct s_pip			t_pip;
typedef struct s_cmd			t_cmd;
typedef struct s_cmd2			t_pipeline;
typedef struct s_built_pair		t_built_pair;
typedef int						(*t_builtin)(t_data *data, t_cmd *cmd);

typedef struct s_built_pair
{
	char		*cmd_name;
	t_builtin	cmd_exe;
}	t_built_pair;


typedef struct s_data
{
	char				**env;
	char				**alias;
	char				**history;
	int					fd_in_original;
	t_pipeline			*pipeline;
	int					exit_code;
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	pid_t				cpid;
}	t_data;

typedef struct s_cmd2
{
	t_cmd			*cmd;
	struct s_cmd2	*next;

	char			and_or;
}	t_pipeline;

// 0 = nothing, 1 = <>, 2 = <<>>
typedef struct s_cmd
{
	char			**cmd_arg;

	pid_t			pid;
	char			*in_file;
	char			*out_file;

	int				fd_in;
	int				fd_out;
	int				in_bit;
	int				out_bit;

	char			error;
	char			sublim;
	struct s_cmd	*next;
}	t_cmd;

///////////////////////////////////////////////////////////////////////////////]
/********************************
		A
********************************/
int			brother_builtin_v2(t_data *data, t_cmd *cmd);
int			child_builtin_v2(t_data *data, t_cmd *cmd);
/********************************
		P - PARSING
********************************/
int			ft_parsing_v2(t_data *data, char *input);
t_cmd		*ft_mario(t_data *data, char *raw_line, int *i, t_cmd *cmd);
void		ft_extract_redirection_v2(char *raw_line, int *i, t_cmd *cmd);
//
char		*ft_extract_words_v2(char *raw_line, int *i);
char		*ft_extract_quotes_v2(char *raw_line, int *i, char quote);
//
void		sublim_pipe_v2(t_data *data, t_pipeline *pipe);
char		*ft_sublim_v2(t_data *data, char *string, int bit);
char		*sublim_dollar_v2(t_data *data, char *raw_arg, int bit);
char		*ft_dollar_v2(t_data *data, char *raw_dollar, int *i);
/********************************
		E - EXEC
********************************/
int			ft_minishell(t_data *data);
int			ft_father(t_data *data);
int			ft_big_brother(t_data *data, t_pipeline *pipeline);
int			ft_lil_brother(t_data *data, t_cmd *cmd);
//
void		ft_exec_v2(t_data *data, t_cmd *cmd, char **env);
/********************************
		B - BUILTIN
********************************/
int			cmd_cd(t_data *data, t_cmd *cmd);
int			cmd_export(t_data *data, t_cmd *cmd);
int			cmd_unset(t_data *data, t_cmd *cmd);
int			cmd_alias(t_data *data, t_cmd *cmd);
int			cmd_exit(t_data *data, t_cmd *cmd);
//
int			cmd_echo(t_data *data, t_cmd *cmd);
int			cmd_type(t_data *data, t_cmd *cmd);
int			cmd_help(t_data *data, t_cmd *cmd);
int			cmd_miaou(t_data *data, t_cmd *cmd);
int			cmd_env(t_data *data, t_cmd *cmd);
int			cmd_history(t_data *data, t_cmd *cmd);
int			cmd_pwd(t_data *data, t_cmd *cmd);
//
void		replace_var(t_data *data, char *to_replace, char *replacement);
char		**pop_entry(char **env, char *to_pop);
/********************************
		T	TOOLS
********************************/
void		dup_close(int fd_replace, int fd_erase);
// 
t_cmd		*new_node(t_cmd *previous);
t_pipeline	*new_cmd(t_pipeline *previous, char c);
// 
char		*rtrn_var_v2(char **env, char *to_extract);
/********************************
		S	SIGNAL
********************************/
void		ini_signal(t_data *data);
void		ini_signal_v2(t_data *data);
void		h_sigint(int sig);
void		fakesig(void);
// 
void		ini_signal_exec(t_data *data);
void		h_sigquit_exec(int sig);
void		h_sigint_exec(int sig);
/********************************
		Y
********************************/
int			initialization(int ac, char **av, char **env, t_data *data);
/********************************
		Z
********************************/
void		clear_cmd(t_data *data);
void		end(t_data *data, int exit_code);

# define INPUT_TXT "\033[0;31mm\033[0;32mi\033[0;33ma\033[0;34mo\033[0;35mu\e[0m > "
# define MSG_REDI "syntax error near unexpected token '%c'\n"

#endif
