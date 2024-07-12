/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Z_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 06:21:51 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/12 02:14:09 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		initialization(int ac, char **av, char **env, t_data *data);
void	clear_cmd(t_data *data);
void	end(t_data *data, int exit_code);

///////////////////////////////////////////////////////////////////////////////]
// ini
int	initialization(int ac, char **av, char **env, t_data *data)
{
	(void)av;
	srand(time(NULL));
	if (ac != 1)
		return (put(ERR"Wrong number of arguments\n"), exit(0), 1);
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
// free double chain data->cmd
void	clear_cmd(t_data *data)
{
	t_cmd2	*ptr1;
	t_cmd	*ptr2;
	t_cmd	*ptr_temp;

	if (!data->cmd)
		return ;
	ptr1 = data->cmd;
	while (ptr1)
	{
		ptr2 = ptr1->cmd;
		while (ptr2)
		{
			free_tab(ptr2->cmd_arg);
			free_s(ptr2->in_file);
			free_s(ptr2->out_file);
			// if (ptr2->fd_in > 0)
			// 	close(ptr2->fd_in);
			// if (ptr2->fd_out > 0)
			// 	close(ptr2->fd_out);
			ptr_temp = ptr2->next;
			free_s(ptr2);
			ptr2 = ptr_temp;
		}
		ptr1 = ptr1->next;
	}
	data->cmd = free_s(data->cmd);
}

///////////////////////////////////////////////////////////////////////////////]
void	end(t_data *data, int exit_code)
{
	free_tab(data->history);
	clear_cmd(data);
	rl_clear_history();
	exit(exit_code);
}
