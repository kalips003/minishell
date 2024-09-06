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

int		cmd_echo(t_data *data, t_cmd *cmd);
int		cmd_type(t_data *data, t_cmd *cmd);
int		cmd_help(t_data *data, t_cmd *cmd);
int		cmd_miaou(t_data *data, t_cmd *cmd);
int		cmd_env(t_data *data, t_cmd *cmd);
int		cmd_history(t_data *data, t_cmd *cmd);
int		cmd_pwd(t_data *data, t_cmd *cmd);

#define MSG_ERR_97 "pwd: error retrieving current directory: getcwd:cannot"
#define MSG_ERR_98 "access parent directories: No such file or directory\n"

//////////////////////////////////////////////////////////////////////////////]
int	cmd_echo(t_data *data, t_cmd *cmd)
{
	int	b;

	(void)data;
	b = 1;
	if (!find_str(cmd->cmd_arg[1], "-n") && len_n(cmd->cmd_arg[1], "n") == 1)
		b++;
	if (cmd->cmd_arg[b])
		put("%#.1t", &cmd->cmd_arg[b]);
	if (b == 1)
		put("\n");
	end(data, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_type(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	end(data, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_help(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	end(data, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_env(t_data *data, t_cmd *cmd)
{
	if (same_str(cmd->cmd_arg[1], "-i") && cmd->cmd_arg[2])
		ft_exec_v2(data, cmd, NULL);
	put("%-t", data->env);
	if (!data->env)
		put("\n");
	end(data, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_history(t_data *data, t_cmd *cmd)
{
	(void)cmd;
	ft_print_cat(data->exit_code, "tis history", 0b10);
	put("%-t", data->history);
	end(data, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_pwd(t_data *data, t_cmd *cmd)
{
	(void)cmd;
	if (access(rtrn_var_v2(data->env, "PWD="), X_OK) == -1)
	{
		perror(ERR2 "access:");
		put(ERR2 MSG_ERR_97 MSG_ERR_98);
		end(data, 1);
	}
	put("%s\n", rtrn_var_v2(data->env, "PWD="));
	end(data, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_miaou(t_data *data, t_cmd *cmd)
{
	(void)cmd;
	ft_print_cat(data->exit_code, "tis memory", 0b10);
	put("% 1000S\n", data->history[0]);
	end(data, 0);
	return (0);
}
