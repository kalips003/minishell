/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_exec_tools1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:30:05 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/13 12:57:47 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	h_734_redirection(t_data *data, t_cmd *cmd);
char	*find_cmd(char *command, char **env);
char	*find_parsing(char *command, char **env);
char	**parse_path(char **env);

///////////////////////////////////////////////////////////////////////////////]
void	h_734_redirection(t_data *data, t_cmd *cmd)
{
	if (cmd->in_file && cmd->out_file && same_str(cmd->in_file, cmd->out_file))
		return (print_fd(2, ERR"same input\\output file '%s'\n", cmd->in_file), end(data, 3));
	if (cmd->in_file && cmd->in_bit == 1)
	{
		cmd->fd_in = open(cmd->in_file, O_RDONLY);
		if (cmd->fd_in < 0)
			return (perror(cmd->in_file), end(data, 5));
		dup_close(cmd->fd_in, STDIN_FILENO);
	}
	else if (cmd->in_file && cmd->in_bit == 2)
		ft_heredoc(data, cmd);
	if (cmd->out_file && cmd->out_bit)
	{
		if (cmd->out_bit == 1)
			cmd->fd_out = open(cmd->out_file, (O_WRONLY | O_CREAT | O_TRUNC), 0777);
		else if (cmd->out_bit == 2)
			cmd->fd_out = open(cmd->out_file, (O_WRONLY | O_CREAT | O_APPEND), 0777);
		if (cmd->fd_out < 0)
			return (perror(cmd->out_file), end(data, 5));
		dup_close(cmd->fd_out, STDOUT_FILENO);
	}
}

///////////////////////////////////////////////////////////////////////////////]
char	*find_cmd(char *command, char **env)
{
	char	*rtrn;

	rtrn = NULL;
	if (!command)
	{
		return (NULL);
	}
	if (find_str(command, "/") >= 0)
	{
		if (access(command, X_OK) == 0)
			return (str("%1s", command));
		return (NULL);
	}
	rtrn = find_parsing(command, env);
	return (rtrn);
}

char	*find_parsing(char *command, char **env)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = parse_path(env);
	if (!paths)
		return (put(RED"ERROR--->$PATH:\n%t\n"RESET, env), NULL);
	cmd = NULL;
	i = -1;
	while (paths[++i])
	{
		cmd = str("%1s/%1s", paths[i], command);
		if (!access(cmd, X_OK))
			break ;
		cmd = free_s(cmd);
	}
	free_tab(paths);
	return (cmd);
}

char	**parse_path(char **env)
{
	while (*env)
	{
		if (*env[0] == 'P' && !find_str(*env, "PATH="))
			return (split(&(*env)[5], ":"));
		env++;
	}
	return (NULL);
}
