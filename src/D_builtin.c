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

int		h_385_builtin(t_data *data, t_cmd *cmd);
void	cmd_cd(t_data *data, t_cmd *cmd);

///////////////////////////////////////////////////////////////////////////////]
int	h_385_builtin(t_data *data, t_cmd *cmd)
{
	if (same_str(cmd->cmd_arg[0], "exit"))
		end(data, 255);
	else if (same_str(cmd->cmd_arg[0], "cd"))
		cmd_cd(data, cmd);
	else if (cmd->cmd_arg && same_str("echo", cmd->cmd_arg[0]) && !find_str(cmd->cmd_arg[1], "-n") && cmd->cmd_arg[2])
	{
		int	i;
		i = 2;
		while (cmd->cmd_arg[i] && cmd->cmd_arg[i + 1])
			i++;
		cmd->cmd_arg[i] = join(cmd->cmd_arg[i], "$\n", 0b10, 0);
	}
	return (0);
}

void	cmd_cd(t_data *data, t_cmd *cmd)
{

}