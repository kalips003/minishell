/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:11:51 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/15 17:11:51 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exec_bigbro(t_data *data);
void	ft_exec(t_data *data, t_cmd *cmd);
int		ft_child(t_data *data, t_cmd *cmd);
int		ft_big_brother(t_data *data, t_cmd2 *cmd);
int		ft_heredoc(t_data *data, t_cmd *cmd);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	takes a cmd link, redirect to correct fd, execute it, end the child
******************************************************************************/
void	ft_exec(t_data *data, t_cmd *cmd)
{
	char	*cmd_exe;

	if (!cmd->cmd_arg)
		(put(ERRM"empty cmd->cmd_arg\n"), end(data, 2));
	h_734_redirection(data, cmd);
	h_385_builtin(data, cmd);
	cmd_exe = find_cmd(cmd->cmd_arg[0], data->env);
	if (!cmd_exe)
	{
		print_fd(2, ERRM"error: %s: not found\n", cmd->cmd_arg[0]);
		end(data, 127);
	}
	if (execve(cmd_exe, cmd->cmd_arg, data->env) == -1)
	{
		perror(ERRM"error execve");
		free_s(cmd_exe);
		end(data, 1);
	}
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	takes data->cmd with arguments, 
		create the big_brother that will do 1 pipeline
	return only:
		0 on succcess and -1 to exit (for now)
******************************************************************************/
int	ft_exec_bigbro(t_data *data)
{
	t_cmd2	*cmd;
	int		rtrn;

	cmd = data->cmd;
	if (!data->cmd)
		return (perror(ERRM"empty args struct"), 1);
	rtrn = 0;
	while (cmd)
	{
		if (!cmd->and_or || (cmd->and_or == '&' && !rtrn) || (cmd->and_or == '|' && rtrn))
			rtrn = ft_big_brother(data, cmd);
		if (WEXITSTATUS(rtrn) == 255)
			return (clear_cmd(data), rtrn);
		cmd = cmd->next;
	}
	return (clear_cmd(data), 0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		does 1 chained list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int	ft_big_brother(t_data *data, t_cmd2 *cmd)
{
	pid_t	pid;
	int		rtrn;
	t_cmd	*cmd2;

	pid = fork();
	if (pid == -1)
		return (perror(ERRM"fork"), 1);
	if (!pid)
	{
		cmd2 = cmd->cmd;
		while (cmd2->next)
		{
			rtrn = ft_child(data, cmd2);
			if (rtrn)
				end(data, rtrn);
			cmd2 = cmd2->next;
		}
		ft_exec(data, cmd2);
	}
	else
		waitpid(pid, &rtrn, 0);
	// put("exit code 1 = %d\n", WEXITSTATUS(rtrn));
	return (rtrn);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		takes a cmd node, return the return value of child
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int	ft_child(t_data *data, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;
	int		rtrn;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(fd[0]), close(fd[1]), 2);
	if (!pid)
	{
		close(fd[0]);
		dup_close(fd[1], STDOUT);
		ft_exec(data, cmd);
	}
	else
	{
		close(fd[1]);
		dup_close(fd[0], STDIN);
		waitpid(pid, &rtrn, 0);
	}
	return (rtrn);
}

///////////////////////////////////////////////////////////////////////////////]
// create child that will pipe the input
int	ft_heredoc(t_data *data, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;
	char	*tmp;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(fd[0]), close(fd[1]), 1);
	if (!pid)
	{
		close(fd[0]);
		while (1)
		{
			tmp = readline(C_415"heredoc:"RESET);
			if (!tmp || same_str(tmp, cmd->in_file))
				(close(fd[1]), free_s(tmp), end(data, 0));
			print_fd(fd[1], "%s\n", tmp);
			tmp = free_s(tmp);
		}
	}
	else
		return (close(fd[1]), dup_close(fd[0], STDIN), wait(NULL), 0);
}