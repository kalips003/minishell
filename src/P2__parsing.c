/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P2__parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:28:22 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/26 14:10:58 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		ft_parsing_v2(t_data *data, char *input);
t_cmd	*ft_mario_v2(t_data *data, char *raw_line, int *i, t_cmd *cmd);
void	ft_extract_redirection_v2(char *raw_line, int *i, t_cmd *cmd);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************

******************************************************************************/
int	ft_parsing_v2(t_data *data, char *input)
{
	int		i;
	t_cmd	*ptr;

	clear_cmd(data);
	if (input[0] == '|' || input[0] == '&' || input[0] == ';')
		return (put(MSG_REDI, input[0]), 1);
	data->cmd = new_cmd(data->cmd, 0);
	if (!data->cmd)
		return (put(ERRM), 1);
	ptr = data->cmd->cmd;
	i = 0;
	while (input[i])
	{
		if (wii(input[i], " \n\t") >= 0 && ++i)
			continue ;
		else if (input[i] == '|' || input[i] == '&' || input[i] == ';')
			ptr = ft_mario_v2(data, input, &i, ptr);
		else if (input[i] == '<' || input[i] == '>')
			ft_extract_redirection_v2(input, &i, ptr);
		else
			ptr->cmd_arg = expand_tab(ptr->cmd_arg, ft_extract_words_v2(input, &i));
		if (!ptr || ptr->error)
			return (1);
	}
	return (0);
}


// sorry MARIO, the princess is in another command
// takes the START of the raw, and work with the &i
// nombre de '|'
// nombre de '&'
// nombre de ';'
t_cmd	*ft_mario_v2(t_data *data, char *raw_line, int *i, t_cmd *cmd)
{
	int		abc = 0;
	int		count = 0;
	int		wii_rtrn;

	wii_rtrn = wii(raw_line[*i], "|&;");
	while (wii_rtrn >= 0 && ++(*i))
	{
		abc |= 1 << wii_rtrn;
		count++;
		wii_rtrn = wii(raw_line[*i], "|&;");
	}
	if (__builtin_popcount(abc) > 1 || count > 2 || (abc & (1 << 1) && count != 2) || (abc & (1 << 2) && count != 1))
		return (put(MSG_REDI, raw_line[*i - 1]), NULL);
	while (wii(raw_line[*i], " \t\n") >= 0)
		(*i)++;
	if (wii(raw_line[*i], "|&;") >= 0 || !raw_line[*i])
		return (put(MSG_REDI, raw_line[*i]), NULL);
	// if (!raw_line[*i])
	// {
	// 	char *to_tail = NULL;
	// 	while (!to_tail)
	// 		to_tail = trim(readline("cmd not finished:"), " \t\n");
	// 	raw_line = join(raw_line, to_tail, );
	// }
	if ((abc & 1) && count == 1)
		return (new_node(cmd));
	else if ((abc & 1) && count == 2)
		return (new_cmd(data->cmd, '|')->cmd);
	else if ((abc & (1 << 1)) && count == 1)
		return (put(ERR2"single '&' will be available next patch, coming next 202....\n"), NULL);
	else if ((abc & (1 << 1)) && count == 2)
		return (new_cmd(data->cmd, '&')->cmd);
	else if (abc & (1 << 2))
		return (new_cmd(data->cmd, '\0')->cmd);
	return (NULL);
}


// input: ">>>> ;alsdkfj;a"
// ab[0] = '<'
// ab[1] = '>'
void	ft_extract_redirection_v2(char *raw_line, int *i, t_cmd *cmd)
{
	int	ab[2];

	ft_memset(ab, 0, sizeof(int) * 2);
	while (raw_line[*i] == '<' && ++(*i))
		ab[0]++;
	while (raw_line[*i] == '>' && ++(*i))
		ab[1]++;
	if ((ab[0] && ab[1]) || ab[0] + ab[1] > 2)
		return (put(MSG_REDI, raw_line[*i - 1]), cmd->error++, (void)0);
	while (wii(raw_line[*i], " \t\n") >= 0)
		(*i)++;
	if (wii(raw_line[*i], "><|&;") >= 0)
		return (put(MSG_REDI, raw_line[*i]), cmd->error++, (void)0);
	if (ab[0])
	{
		cmd->in_bit = ab[0];
		cmd->in_file = free_s(cmd->in_file);
		cmd->in_file = ft_extract_words_v2(raw_line, i);
	}
	else if (ab[1])
	{
		cmd->out_bit = ab[1];
		cmd->out_file = free_s(cmd->out_file);
		cmd->out_file = ft_extract_words_v2(raw_line, i);
	}
}