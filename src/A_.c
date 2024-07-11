/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:01:46 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/11 17:23:30 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(t_data *data);
// int	ft_builtin(t_data *data, char *input);
// int	ft_pwd(t_data *data, char *input);
///////////////////////////////////////////////////////////////////////////////]
// 1 loop pper input
int	ft_minishell(t_data *data)
{
	char	*input;
	char	*input_txt;

	input_txt = str(" \033[38;5;%dmm\033[38;5;%dmi\033[38;5;%dma\033[38;5;%dmo\033[38;5;%dmu\e[0m > ", \
		rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256);
	input = readline(input_txt);
	free_s(input_txt);
	input = trim_white(input, " \n\t");
	if (!input)
		return (0);
	if (ft_parsing(data, input))
		return (clear_cmd(data), 0);
	data->history = expand_tab(data->history, input);
	add_history(input);
	return (ft_exec_bigbro(data));
}


///////////////////////////////////////////////////////////////////////////////]
// exxecute built in, 
// return 1 if built in executed, or no cmd
// 0 otherwise
// int	ft_builtin(t_data *data, char *input)
// {

// 	if (same_str(input, "exit"))
// 		end(data, 0);
// 	if (len_n(input, " \n\t") <= 0)
// 		return (1);
// 	data->history = expand_tab(data->history, input);
// 	add_history(input);
// 	if (find_str(input, "pwd") == 0)
// 		return (ft_pwd(data, input), 1);
// 	return (0);
// }

// #define BUFF_PWD 1024
// ///////////////////////////////////////////////////////////////////////////////]
// int	ft_pwd(t_data *data, char *input)
// {
// 	char	buffer[BUFF_PWD + 1];

// 	ft_memset(buffer, 0, BUFF_PWD + 1);
// 	if (!getcwd(buffer, BUFF_PWD))
// 		return (perror(ERRM"getcwd"), 1);
// 	put(C_355"%s\n"RESET, buffer);
// 	return (1);
// }
