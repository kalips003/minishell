/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_parsing_tools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:26:09 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/13 15:17:42 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sublim(t_data *data, t_cmd *cmd);
char	*sublim_helper(t_data *data, char *string);
static char	*sublim_helper2(t_data *data, char *string);
t_cmd		*new_node(t_cmd *previous);
t_cmd2		*new_cmd(t_cmd2 *previous, char c);

///////////////////////////////////////////////////////////////////////////////]
// cmd1 < $FILE | cmd2 "> outfile" | cmd3 && cmd3 >> appendfile
// subliiim one child's char **
void	sublim(t_data *data, t_cmd *cmd)
{
	char	**ptr3;

	if (!cmd->cmd_arg)
		(print_fd(2, ERRM"empty cmd->cmd_arg\n"), end(data, 2));
	ptr3 = cmd->cmd_arg;
	while (ptr3 && *ptr3)
	{
		*ptr3 = sublim_helper(data, *ptr3);
		ptr3++;
	}
}

char	*sublim_helper(t_data *data, char *string)
{
	if (string[0] == '\'')
		return (trim_white(string, "'"));
	else if (string[0] == '"')
		string = trim_white(string, "\"");
	string = sublim_helper2(data, string);
	if (!string)
		(print_fd(2, ERRM"malloc?\n"), end(data, 45));
	return (string);

}

static char	*sublim_helper2(t_data *data, char *string)
{
	int		i;
	int		lenght;
	char	*name;
	char	*value;
	char	*string2;

	i = -1;
	while (string[++i])
	{
		if (string[i] == '$' && string[i + 1] && wii(string[i + 1], "$ \n\t\"\n") < 0)
		// ft_replace_var(string, &string[i + 1])
		{
			name = str("%1.*s", len_m(&string[i + 1], "$ \n\t\"\n"), &string[i + 1]);
			lenght = len(name);
			value = getenv(name);
			name = free_s(name);
			string2 = str("%1.*s%*s%1s", i, string, !!(value) , value, &string[i + 1 +lenght]);
			free_s(string);
			string = string2;
		}
	}
	return (string);
	// if ($$)
	// 	get_process_pid
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