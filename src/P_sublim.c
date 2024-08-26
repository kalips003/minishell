/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P_sublim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:26:09 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/26 19:07:50 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void		sublim_child(t_data *data, t_cmd *cmd);
// char		*ft_sublim(t_data *data, char *string);
// static char	*sublim_dollar(t_data *data, char *raw_arg);

// // cmd1 < $FILE | cmd2 "> outfile" | cmd3 && cmd3 >> appendfile
// ///////////////////////////////////////////////////////////////////////////////]
// // sublim one child
// void	sublim_child(t_data *data, t_cmd *cmd)
// {
// 	char	**ptr3;

// 	if (cmd->sublim)
// 		return ;
// 	if (!cmd->cmd_arg)
// 		cmd->cmd_arg = expand_tab(cmd->cmd_arg, str("cat"));
// 	ptr3 = cmd->cmd_arg;
// 	while (ptr3 && *ptr3)
// 	{
// 		*ptr3 = ft_sublim(data, *ptr3);
// 		ptr3++;
// 	}
// 	if (cmd->in_bit != 2)
// 		cmd->in_file = ft_sublim(data, cmd->in_file);
// 	cmd->out_file = ft_sublim(data, cmd->out_file);
// 	cmd->sublim = 1;
// }

// // takes: "abc"'ab$5"4'baaac"$5"$5
// // >	abcab$5"4baaac($5)($5)
// char	*ft_sublim(t_data *data, char *string)
// {
// 	char	*sublim;
// 	char	*str1;
// 	int		i;

// 	if (!string)
// 		return (NULL);
// 	sublim = NULL;
// 	i = 0;
// 	while (string[i])
// 	{
// 		if (string[i] == '\'')
// 			sublim = join(sublim, trim(ft_extract_quotes(&string[i], &i, string[i]), "\'"), 0b11, 0);
// 		else if (string[i] == '\"')
// 		{
// 			str1 = sublim_dollar(data, trim(ft_extract_quotes(&string[i], &i, string[i]), "\""));
// 			sublim = join(sublim, str1, 0b11, 0);
// 		}
// 		else
// 		{
// 			str1 = sublim_dollar(data, ft_extract_word(&string[i], &i));
// 			sublim = join(sublim, str1, 0b11, 0);
// 		}
// 	}
// 	if (!sublim)
// 		return (print_fd(2, ERR4"malloc? sublim!\n"), string);
// 	free_s(string);
// 	return (sublim);

// }

// // recieve: ecg'$5321=' i > ecg'($5) i
// static char	*sublim_dollar(t_data *data, char *raw_arg)
// {
// 	int		j;
// 	int		b;
// 	char	*rtrn;
// 	char	*var;

// 	rtrn = NULL;
// 	j = 0;
// 	while (raw_arg[j])
// 	{
// 		if (raw_arg[j] == '$' && raw_arg[j + 1] == '$' && ++j && ++j)
// 			rtrn = join(rtrn, str("%d", getpid()), 0b11, 0);
// 		else if (raw_arg[j] == '$' && raw_arg[j + 1] == '?' && ++j && ++j)
// 			rtrn = join(rtrn, str("%d", WEXITSTATUS(data->exit_code)), 0b11, 0);
// 		else if (raw_arg[j] == '$')
// 		{
// 			b = len_m(&raw_arg[j + 1], " \t\n$;");
// 			if (!b && ++j)
// 				rtrn = join(rtrn, "$", 0b10, 0);
// 			else
// 			{
// 				var = str("%1.*s=", b, &raw_arg[j + 1]);
// 				j += b + 1;
// 				rtrn = join(rtrn, rtrn_var_v2(data->env, var), 0b10, 0);
// 				free_s(var);
// 			}
// 		}
// 		else
// 		{
// 			b = len_m(&raw_arg[j], "$");
// 			rtrn = join(rtrn, &raw_arg[j], 0b10, b);
// 			j += b;
// 		}
// 	}
// 	free_s(raw_arg);
// 	return (rtrn);
// }
