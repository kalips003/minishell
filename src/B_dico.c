/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_dico.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umosse <umosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:01:46 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/31 16:30:26 by umosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	brother_builtin_v2(t_data *data, t_cmd *cmd);
int	child_builtin_v2(t_data *data, t_cmd *cmd);

static const t_built_pair	g_builtin[] = {
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
