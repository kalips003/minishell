/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D_.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:21:53 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/11 17:21:53 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int		h_385_builtin(t_data *data, t_cmd *cmd);
void	cmd_cd(t_data *data, t_cmd *cmd);
void	cmd_export(t_data *data, t_cmd *cmd);

///////////////////////////////////////////////////////////////////////////////]
int	h_385_builtin(t_data *data, t_cmd *cmd)
{
	if (same_str(cmd->cmd_arg[0], "exit"))
		end(data, 0);
	else if (same_str(cmd->cmd_arg[0], "env"))
		return (put("%t", data->env), 1);
	else if (same_str(cmd->cmd_arg[0], "history"))
		return (put("%t", data->history), 0);
	else if (same_str(cmd->cmd_arg[0], "pwd"))
		return (put("%s\n", rtrn_var(data->env, "PWD=") + 4), 0);
	// else if (same_str(cmd->cmd_arg[0], "cd"))
	// 	return (cmd_cd(data, cmd), 1);
	else if (same_str(cmd->cmd_arg[0], "export"))
		cmd_export(data, cmd);
	else if (cmd->cmd_arg && same_str("echo", cmd->cmd_arg[0]) && !find_str(cmd->cmd_arg[1], "-n") && cmd->cmd_arg[2])
	{
		int	i;
		i = 2;
		while (cmd->cmd_arg[i] && cmd->cmd_arg[i + 1])
			i++;
		cmd->cmd_arg[i] = join(cmd->cmd_arg[i], "$\n", 0b10, 0);
	}
	return (1);
}

///////////////////////////////////////////////////////////////////////////////]
#define BUF_WD 1024
// HOME=/home/kalipso
// SHELL=/usr/bin/zsh
void	cmd_cd(t_data *data, t_cmd *cmd)
{
	char	*new_pwd;
	char	*new_oldpwd;
	char	buf_newpath[BUF_WD];
	
	if (!cmd->cmd_arg[1])
		cmd->cmd_arg = expand_tab(cmd->cmd_arg, str("%1s", rtrn_var(data->env, "HOME=") + 5));

	if (chdir(cmd->cmd_arg[1]))
		(perror(ERR9"cd bad dirrrecctory?:"), end(data, 9));
	ft_memset(buf_newpath, 0, BUF_WD);
	getcwd(buf_newpath, BUF_WD);
	if (!*buf_newpath)
		(perror(ERR9"getcwd"), end(data, 9));
	new_pwd = str("PWD=%1s", buf_newpath);
	new_oldpwd = str("OLDPWD=%1s", &(rtrn_var(data->env, "PWD=")[4]));
	replace_var(data, "PWD=", new_pwd);
	replace_var(data, "OLDPWD=", new_oldpwd);
}

// export var="text"
void	cmd_export(t_data *data, t_cmd *cmd)
{
	char	*first_arg = cmd->cmd_arg[1];
	if (wii('=', first_arg) <= 0)
		return (put(ERR0"bad assignement\n"), (void)0);
	// char	*var = str("%1.*s", len_m(first_arg, "="), first_arg);

	// if (!cmd->cmd_arg[1])
	// 	return (put("%t", data->env), (void)0);
	// 	// cmd->cmd_arg = expand_tab(cmd->cmd_arg, str("%1s", rtrn_var(data->env, "HOME=") + 5));
	


	// new_pwd = str("PWD=%1s", buf_newpath);
	// new_oldpwd = str("OLDPWD=%1s", &(rtrn_var(data->env, "PWD=")[4]));

	// replace_var(data, "PWD=", new_pwd);
	// replace_var(data, "OLDPWD=", new_oldpwd);

	// end(data, 0);
}
*/