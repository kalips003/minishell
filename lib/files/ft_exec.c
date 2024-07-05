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

#include "../../inc/libft.h"

void		ft_exec(char *raw_cmd, char **env);
static char	**parse_path(char **env);
static char	*find_parsing(char *command, char **env);
static char	*find_cmd(char *command, char **env);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	takes a raw cmd with arguments, execute it, end the child
******************************************************************************/
// raw_cmd = "ls -la -lb"
void	ft_exec(char *raw_cmd, char **env)
{
	char	**argve;
	char	*cmd;

	argve = split(raw_cmd, " ");
	if (!argve)
		return ;
	cmd = find_cmd(argve[0], env);
	if (!cmd)
	{
		dup2(STDERR_FILENO, 1);
		put("error: %s: not found\n", argve[0]);
		free_tab(argve);
		exit(127);
	}
	if (execve(cmd, argve, env) == -1)
	{
		dup2(STDERR_FILENO, 1);
		perror("error execve");
		free_tab(argve);
		free(cmd);
		exit(1);
	}
}

///////////////////////////////////////////////////////////////////////////////]
static char	**parse_path(char **env)
{
	while (*env)
	{
		if (*env[0] == 'P' && !find_str(*env, "PATH="))
			return (split(&(*env)[5], ":"));
		env++;
	}
	return (NULL);
}

static char	*find_parsing(char *command, char **env)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = parse_path(env);
	if (!paths)
		return (put(RED"ERROR--->$PATH:\n%t"RESET, env), NULL);
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

static char	*find_cmd(char *command, char **env)
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
