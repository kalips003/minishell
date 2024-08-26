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

void	child_builtin(t_data *data, t_cmd *cmd);
int		cmd_echo(t_data *data, t_cmd *cmd);
int		cmd_type(t_data *data, t_cmd *cmd);
int		cmd_help(t_data *data, t_cmd *cmd);
int		cmd_miaou(t_data *data, t_cmd *cmd);
int		cmd_env(t_data *data, t_cmd *cmd);
int		cmd_history(t_data *data, t_cmd *cmd);
int		cmd_pwd(t_data *data, t_cmd *cmd);

#define MSG_ERR_987 "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"
///////////////////////////////////////////////////////////////////////////////]
// 	cmd_echo; cmd_type; cmd_help; cmd_miaou;
void	child_builtin(t_data *data, t_cmd *cmd)
{
	t_built_pair	*ptr;
	
	if (brother_builtin(data, cmd))
		end(data, WEXITSTATUS(data->exit_code));
	else if (same_str(cmd->cmd_arg[0], "env"))
	{
		put("%-t", data->env);
		if (!data->env)
			put("\n");
		end(data, 0);
	}
	else if (same_str(cmd->cmd_arg[0], "history"))
		(put("%-t", data->history), end(data, 0));
	else if (same_str(cmd->cmd_arg[0], "pwd"))
	{
		if (access(rtrn_var_v2(data->env, "PWD="), X_OK) == -1)
			return (put(ERR2 MSG_ERR_987), end(data, 0));
		put("%s\n", rtrn_var_v2(data->env, "PWD="));
		end(data, 0);
	}
	ptr = data->builtin - 1;
	while ((++ptr)->cmd_exe && ptr->cmd_name)
	{
		if (same_str(cmd->cmd_arg[0], ptr->cmd_name))
		{
			data->exit_code = ptr->cmd_exe(data, cmd);
			end(data, WEXITSTATUS(data->exit_code));
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
int	cmd_echo(t_data *data, t_cmd *cmd)
{
	int	i;
	int	b;
	(void)data;
	b = 1;
	if (!find_str(cmd->cmd_arg[1], "-n") && cmd->cmd_arg[2])
	{
		i = 2;
		b++;
		while (cmd->cmd_arg[i] && cmd->cmd_arg[i + 1])
			i++;
		cmd->cmd_arg[i] = join(cmd->cmd_arg[i], "$\n", 0b10, 0);
	}
	if (cmd->cmd_arg[b])
		put("%#.1t\n", &cmd->cmd_arg[b]);
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
		put(ERR2 MSG_ERR_987);
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