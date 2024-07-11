/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_parsing_tools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:26:09 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/12 00:16:01 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sublim(t_data *data);
static char	*sublim_helper(t_data *data, char *string);
t_cmd		*new_node(t_cmd *previous);
t_cmd2		*new_cmd(t_cmd2 *previous, char c);

///////////////////////////////////////////////////////////////////////////////]
// cmd1 < $FILE | cmd2 "> outfile" | cmd3 && cmd3 >> appendfile
void	sublim(t_data *data)
{
	t_cmd2	*ptr;
	t_cmd	*ptr2;
	char	**ptr3;

	ptr = data->cmd;
	while (ptr)
	{
		ptr2 = ptr->cmd;
		while (ptr2)
		{
			ptr3 = ptr2->cmd_arg;
			while (ptr3 && *ptr3)
			{
				*ptr3 = sublim_helper(data, *ptr3);
				ptr3++;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

static char	*sublim_helper(t_data *data, char *string)
{
	(void)data;
	return (trim_white(string, "'\""));
}

///////////////////////////////////////////////////////////////////////////////]
// 		return new node 1 command
t_cmd	*new_node(t_cmd *previous)
{
	t_cmd	*next;

	next = (t_cmd *)mem(0, sizeof(t_cmd));
	if (!next)
		return (NULL);
	if (previous)
		previous->next = next;
	return (next);
}

// 		return new node 1 pipeline
t_cmd2	*new_cmd(t_cmd2 *previous, char c)
{
	t_cmd2	*next;

	next = (t_cmd2 *)mem(0, sizeof(t_cmd2));
	if (!next)
		return (put(ERRM"error (4)"), NULL);
	if (previous)
	{
		while (previous->next)
			previous = previous->next;
		previous->next = next;
	}
	next->cmd = new_node(NULL);
	next->and_or = c;
	if (!next->cmd)
		return (put(ERRM"error (4)"), NULL);
	return (next);
}