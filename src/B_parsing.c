/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:28:22 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/13 14:35:36 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_parsing(t_data *data, char *input);
static t_cmd	*ft_mario(t_data *data, char *raw_line, int *i, t_cmd *cmd);
static void		ft_extract_redirection(char *raw_line, int *i, t_cmd *cmd_structd);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	its a child; takes a cmd struct execute it
******************************************************************************/
int	ft_parsing(t_data *data, char *input)
{
	int		i;
	t_cmd	*ptr;

	clear_cmd(data);
	if (input[0] == '|' || input[0] == '&')
		return (put(MSG_REDI, input[0]), 1);
	data->cmd = new_cmd(data->cmd, 0);
	if (!data->cmd)
		return (1);
	ptr = data->cmd->cmd;
	i = -1;
	while (input[++i])
	{
		if (wii(input[i], " \n\t") >= 0)
			continue ;
		else if (input[i] == '|' || input[i] == '&')
			ptr = ft_mario(data, &input[i], &i, ptr);
		else if (input[i] == '<' || input[i] == '>')
			ft_extract_redirection(&input[i], &i, ptr);
		else
			ptr->cmd_arg = expand_tab(ptr->cmd_arg, ft_extract_word(&input[i], &i));
		i--;
		if (!ptr || ptr->error)
			return (1);
	}
	return (0);
}


///////////////////////////////////////////////////////////////////////////////]
// sorry MARIO, the princess is in another command
static t_cmd	*ft_mario(t_data *data, char *raw_line, int *i, t_cmd *cmd)
{
	int		i2[2];
	int		j;

	i2[0] = 0;
	i2[1] = 0;
	j = 0;
	while (raw_line[i2[0]] == '|' && ++(*i) && ++j)
		i2[0]++;
	while (raw_line[i2[1]] == '&' && ++(*i) && ++j)
		i2[1]++;
	if ((i2[0] && i2[1]) || i2[0] + i2[1] > 2)
		return (put(MSG_REDI, raw_line[0]), NULL);
	// put("rawline = %s;i=%d [%c]\n", raw_line, *i, raw_line[*i]);
	while (wii(raw_line[j], " \t\n") >= 0 && ++j)
		(*i)++;
	if (wii(raw_line[j], "|&") >= 0)//			iif || isnt termiinated?
		return (put(MSG_REDI, raw_line[0]), NULL);
	if (i2[0] == 1)
		return (new_node(cmd));
	else if (i2[0] == 2)
		return (new_cmd(data->cmd, '|')->cmd);
	else if (i2[1] == 1)
		return (put("single '&' will be available next patch, coming next 202....\n"), NULL);
	else if (i2[1] == 2)
		return (new_cmd(data->cmd, '&')->cmd);
	return (NULL);
}


///////////////////////////////////////////////////////////////////////////////]
// < << > >>     "heelllo"
static void	ft_extract_redirection(char *raw_line, int *i, t_cmd *cmd_structd)
{
	int		i2[2];
	int		j;

	i2[0] = 0;
	i2[1] = 0;
	j = 0;
	while (raw_line[i2[0]] == '<' && ++(*i) && ++j)
		i2[0]++;
	while (raw_line[i2[1]] == '>' && ++(*i) && ++j)
		i2[1]++;
	if ((i2[0] && i2[1]) || i2[0] + i2[1] > 2)
		return (put(MSG_REDI, raw_line[0]), cmd_structd->error++, (void)0);
	while (wii(raw_line[j], " \t\n") >= 0 && ++j)
		(*i)++;
	if (wii(raw_line[j], "><|&") >= 0)
		return (put(MSG_REDI, raw_line[0]), cmd_structd->error++, (void)0);
	if (i2[0])
	{
		cmd_structd->in_bit = i2[0];
		cmd_structd->in_file = free_s(cmd_structd->in_file);
		cmd_structd->in_file = ft_extract_word(&raw_line[j], i);
	}
	else if (i2[1])
	{
		cmd_structd->out_bit = i2[1];
		cmd_structd->out_file = free_s(cmd_structd->out_file);
		cmd_structd->out_file = ft_extract_word(&raw_line[j], i);
	}
}
