/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:43 by marvin            #+#    #+#             */
/*   Updated: 2024/07/13 12:08:06 by kalipso          ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>


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
# define STDERR 1

typedef struct s_pip	t_pip;
typedef struct s_cmd	t_cmd;
typedef struct s_cmd2	t_cmd2;

typedef struct s_data
{
	char	**env;
	char	**history;
	int		fd_in_original;
	t_cmd2	*cmd;
}	t_data;

typedef struct s_cmd
{
// 0 = nothing, 1 = <>, 2 = <<>>
	char	**cmd_arg;

	char	*in_file;
	char	*out_file;


	int		fd_in;
	int		fd_out;
	int		in_bit;
	int		out_bit;

	int		error;
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_cmd2
{
	t_cmd	*cmd;
	struct s_cmd2	*next;

	char	and_or;
	int		error;
}	t_cmd2;

typedef struct s_pip
{
	int	infile;
	int	outfile;
	int	i;
	int	first_cmd;
}	t_pip;


///////////////////////////////////////////////////////////////////////////////]
/********************************
		A
********************************/
int		ft_minishell(t_data *data);
// int		ft_builtin(t_data *data, char *input);
// int		ft_pwd(t_data *data, char *input);
/********************************
		B - PARTHING
********************************/
int				ft_parsing(t_data *data, char *input);
// 
char		*ft_extract_word(char *raw_line, int *i);
// 
void		sublim(t_data *data);
t_cmd		*new_node(t_cmd *previous);
t_cmd2		*new_cmd(t_cmd2 *previous, char c);

/********************************
		C
********************************/
void	h_734_redirection(t_data *data, t_cmd *cmd);
int		h_385_builtin(t_data *data, t_cmd *cmd);
char	**parse_path(char **env);
char	*find_parsing(char *command, char **env);
char	*find_cmd(char *command, char **env);
// 
int		ft_exec_bigbro(t_data *data);
void	ft_exec(t_data *data, t_cmd *cmd);
int		ft_child(t_data *data, t_cmd *cmd);
int		ft_big_brother(t_data *data, t_cmd2 *cmd);
void		ft_heredoc(t_data *data, t_cmd *cmd);
/********************************
		D
********************************/

/********************************
		T	TOOLS
********************************/
char	*trim_white(char *input, char *dico);
void	dup_close(int fd_replace, int fd_erase);


/********************************
		Z
********************************/
int		initialization(int ac, char **av, char **env, t_data *data);
void	clear_cmd(t_data *data);
void	end(t_data *data, int exit_code);

#define INPUT_TXT "\033[0;31mm\033[0;32mi\033[0;33ma\033[0;34mo\033[0;35mu\e[0m > "
#define MSG_REDI "syntax error near unexpected token '%c'\n"

#endif
