/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:01:46 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/27 01:09:36 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	brother_builtin_v2(t_data *data, t_cmd *cmd);
int	child_builtin_v2(t_data *data, t_cmd *cmd);
void	ft_exec_v2(t_data *data, t_cmd *cmd, char **env);
int	ft_big_brother_v2(t_data *data, t_pipeline *pipeline);
static void	h_bigbro(t_data *data, t_cmd *ptr_cmd);
int	ft_child_v2(t_data *data, t_cmd *cmd);

// Declare the built-in arrays as const static
static const t_built_pair g_builtin[] = {
	{"cd", cmd_cd},
	{"export", cmd_export},
	{"unset", cmd_unset},
	{"alias", cmd_alias},
	{"exit", cmd_exit},
	{"echo", cmd_echo},
	{"type", cmd_type},
	{"help", cmd_help},
	{"miaou", cmd_miaou},
	{"env", cmd_env},
	{"history", cmd_history},
	{"pwd", cmd_pwd},
	{NULL, NULL}
};

///////////////////////////////////////////////////////////////////////////////]
// cmd_cd; cmd_export; cmd_unset; cmd_alias;
// done only if a single command
int	brother_builtin_v2(t_data *data, t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = -1;
	while (g_builtin[++i].cmd_exe && i <= 4)
	{
		if (same_str(cmd->cmd_arg[0], g_builtin[i].cmd_name))
		{
			data->exit_code = g_builtin[i].cmd_exe(data, cmd) << 2;
			return (1);
		}
	}
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
// cmd_cd; cmd_export; cmd_unset; cmd_alias;
// done only if a single command
// return 1 only if the brother_builting got done
// exit if child_builtin
// return 0 if no builtin
int	child_builtin_v2(t_data *data, t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = -1;
	while (g_builtin[++i].cmd_exe)
	{
		if (same_str(cmd->cmd_arg[0], g_builtin[i].cmd_name))
		{
			data->exit_code = g_builtin[i].cmd_exe(data, cmd);
			return (1);
		}
	}
	return (0);
}



/*******************************************************************************
	takes a cmd link, redirect to correct fd, execute it, end the child
******************************************************************************/
void	ft_exec_v2(t_data *data, t_cmd *cmd, char **env)
{
	char	*cmd_exe;

	if (!cmd)
		end(data, 0);
	h_734_redirection(data, cmd);
	if (child_builtin_v2(data, cmd))
		end(data, data->exit_code);
	cmd_exe = find_cmd(cmd->cmd_arg[0], data->env);
	if (!cmd_exe)
	{
		print_fd(2, ERR6"%s: not found (%s)\n", cmd->cmd_arg[0], strerror(errno));
		end(data, 127);
	}
	if (execve(cmd_exe, cmd->cmd_arg, env) == -1)
	{
		print_fd(2, ERR6"error execve (%s)\n", strerror(errno));
		// perror(ERR7"error execve");
		free_s(cmd_exe);
		end(data, 1);
	}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		does 1 chained list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int	ft_big_brother_v2(t_data *data, t_pipeline *pipeline)
{
	pid_t	pid;

	if (!pipeline->cmd->next && brother_builtin_v2(data, pipeline->cmd))
		return (0);
	pid = fork();
	if (pid == -1)
		return (perror(ERR7"fork"), 1);
	if (!pid)
		h_bigbro(data, pipeline->cmd);
	waitpid(pid, &data->exit_code, 0);
	return (0);
}

static void	h_bigbro(t_data *data, t_cmd *ptr_cmd)
{
	t_cmd *first_cmd;
	
	first_cmd = ptr_cmd;
	while (ptr_cmd)
	{
		ft_child_v2(data, ptr_cmd);
		ptr_cmd = ptr_cmd->next;
	}
	ptr_cmd = first_cmd;
	while (ptr_cmd)
	{
		int wait = waitpid(ptr_cmd->pid, &data->exit_code, 0);
		wait++;
		ptr_cmd = ptr_cmd->next;
	}
	end(data, WEXITSTATUS(data->exit_code));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		takes a cmd node, return the return value of child
		echo a | sleep 5 | echo b
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int	ft_child_v2(t_data *data, t_cmd *cmd)
{
	int		fd[2];

	if (cmd->next)
		if (pipe(fd) == -1)
			(perror(ERR7"pipe"), end(data, 66));
	cmd->pid = fork();
	if (cmd->pid == -1)
		(perror(ERR7"fork"), close(fd[0]), close(fd[1]), end(data, 66));
	if (!cmd->pid)
	{
		if (cmd->next)
			(close(fd[0]), dup_close(fd[1], STDOUT));
		ft_exec_v2(data, cmd, data->env);
	}
	else if (cmd->next)
		(close(fd[1]), dup_close(fd[0], STDIN));
	return (0);
}