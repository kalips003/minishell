/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_outils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:11:46 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/28 17:19:52 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	same_str_n(char *gnl0, char *stop_w);
void		dup_close(int fd_replace, int fd_erase);
void		ft_heredoc(char **av);
void		ft_child(char *raw_cmd, char **env, t_pip *pip);

///////////////////////////////////////////////////////////////////////////////]
// add the \n to arg, check if same as gnl(0)
static int	same_str_n(char *gnl0, char *stop_w)
{
	char	*temp;
	int		i;

	i = 0;
	temp = str("%1s\n", stop_w);
	if (same_str(gnl0, temp))
		i++;
	free(temp);
	return (i);
}

///////////////////////////////////////////////////////////////////////////////]
// dup2 and close fd
void	dup_close(int fd_replace, int fd_erase)
{
	if (fd_replace < 0 || fd_erase < 0)
		return ;
	dup2(fd_replace, fd_erase);
	close(fd_replace);
}

///////////////////////////////////////////////////////////////////////////////]
// add the \n to arg, check if same as gnl(0)
void	ft_heredoc(char **av)
{
	int		fd[2];
	pid_t	pid;
	char	*tmp;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (!pid)
	{
		close(fd[0]);
		while (1)
		{
			tmp = gnl(0);
			if (!tmp || same_str_n(tmp, av[2]))
				(close(fd[1]), free_s(tmp), exit(0));
			print_fd(fd[1], "%s", tmp);
			tmp = free_s(tmp);
		}
	}
	else
		(close(fd[1]), dup_close(fd[0], STDIN), wait(NULL));
}

///////////////////////////////////////////////////////////////////////////////]
// ./pipex infile cmd1 cmd2 cmd3 outfile = 6
void	ft_child(char *raw_cmd, char **env, t_pip *pip)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (!pid)
	{
		close(pip->outfile);
		close(fd[0]);
		dup_close(fd[1], STDOUT);
		ft_exec(raw_cmd, env);
	}
	else
	{
		close(fd[1]);
		dup_close(fd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
}
