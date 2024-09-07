/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_builtin_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 04:12:38 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/16 04:12:38 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_cd(t_data *data, t_cmd *cmd);
int	cmd_export(t_data *data, t_cmd *cmd);
int	cmd_unset(t_data *data, t_cmd *cmd);
int	cmd_alias(t_data *data, t_cmd *cmd);
int	cmd_exit(t_data *data, t_cmd *cmd);

#define BUF_WD 1024

///////////////////////////////////////////////////////////////////////////////]
// HOME=/home/kalipso
// SHELL=/usr/bin/zsh
int	cmd_cd(t_data *data, t_cmd *cmd)
{
	char	*new_pwd;
	char	*new_oldpwd;
	char	buf_newpath[BUF_WD];

	if (!cmd->cmd_arg[1])
		cmd->cmd_arg = expand_tab(cmd->cmd_arg,
				str("%1s", rtrn_var_v2(data->env, "HOME=")));
	if (chdir(cmd->cmd_arg[1]))
		return (perror(ERR9"cd bad directory"), 1);
	ft_memset(buf_newpath, 0, BUF_WD);
	if (!getcwd(buf_newpath, BUF_WD))
		return (perror(ERR8"erreur test"), 1);
	if (!*buf_newpath)
		return (perror(ERR9"getcwd"), 1);
	new_pwd = str("PWD=%1s", buf_newpath);
	new_oldpwd = str("OLDPWD=%1s", rtrn_var_v2(data->env, "PWD="));
	replace_var(data, "PWD=", new_pwd);
	replace_var(data, "OLDPWD=", new_oldpwd);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
// export var="text"
// export var+="text"
/*
bash-5.1$ export =
bash: export: `=': not a valid identifier

bash-5.1$ export AB===j===hflakjdf?
bash-5.1$ echo $AB
==j===hflakjdf?



*/
int	cmd_export(t_data *data, t_cmd *cmd)
{
	char	*first_arg;
	char	*var;
	int		first_equal;
	// int		temp_equal;

	first_arg = cmd->cmd_arg[1];
	first_equal = wii('=', first_arg);
	if (!first_arg || first_equal < 0)
		return (put("%+-t", data->env, "export "), 0);
	// temp_equal = len_m(&first_arg[first_equal],
	// 		";|&=()[]{}!@#^*+-/\\~%?:,<>$\'\"");
	var = str("%1.*s", len_m(first_arg, "=") + 1, first_arg);
	replace_var(data, var, str("%1s", first_arg));
	free_s(var);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_unset(t_data *data, t_cmd *cmd)
{
	char	*first_arg;
	char	*var;

	first_arg = cmd->cmd_arg[1];
	if (!first_arg)
		return (0);
	var = str("%1s=", first_arg);
	data->env = pop_entry(data->env, var);
	free_s(var);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
// alias no cmd->cmd_arg[1] = display all alias
// alias update='sudo apt update; sudo apt upgrade'
int	cmd_alias(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_exit(t_data *data, t_cmd *cmd)
{
	int	err;
	int	rtrn_atoi;

	err = 0;
	if (tab_size(cmd->cmd_arg) > 2)
		return (put(ERR1"exit: too many arguments\n"), 1);
	if (cmd->cmd_arg && cmd->cmd_arg[1])
	{
		rtrn_atoi = ft_atoi(cmd->cmd_arg[1], &err);
		if (err)
		{
			put(ERR1"exit: %s: numeric argument required\n", cmd->cmd_arg[1]);
			end(data, WEXITSTATUS(0x0200));
		}
		else
			end(data, WEXITSTATUS(rtrn_atoi << 8) & 0xff);
	}
	end(data, 0);
	return (0);
}
