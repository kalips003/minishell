/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   E_exec_family.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 04:12:25 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/16 04:12:25 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_minishell(t_data *data);
int	ft_father(t_data *data);
// int	ft_big_brother(t_data *data, t_pipeline *cmd);
int	ft_child(t_data *data, t_cmd *cmd);

extern int g_pid;

// #define INPUT_TEXT " \033[38;5;%dmm\033[38;5;%dmi\033[38;5;%dma\033[38;5;%dmo\033[38;5;%dmu\e[0m (%d)> "
#define INPUT_TEXT "\001 \033[38;5;%dmm\033[38;5;%dmi\033[38;5;%dma\033[38;5;%dmo\033[38;5;%dmu\e[0m (\033[0;3%dm%d\e[0m): \002"
// #define INPUT_TEXT " input> "
///////////////////////////////////////////////////////////////////////////////]
// 1 loop per input
int	ft_minishell(t_data *data)
{
	char	*input;
	char	*input_txt;

	// input_txt = str("\033[0;35;%dm (%d) input> \e[0m", WEXITSTATUS(data->exit_code), WEXITSTATUS(data->exit_code));
	input_txt = str(INPUT_TEXT RESET, rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256,
		1 + !(WEXITSTATUS(data->exit_code)), WEXITSTATUS(data->exit_code));
	input = readline(input_txt);
	free_s(input_txt);
	if (!input)
		(put("exit\n"), end(data, 0));
	input = trim(input, " \n\t");
	if (!input)
		return (0);
	if (ft_parsing_v2(data, input))
	{
		data->exit_code = 0x0200;
		return (clear_cmd(data), free_s(input), 0);
	}
	data->history = expand_tab(data->history, input);
	add_history(input);
	return (ft_father(data));
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	takes data->cmd with arguments,
		create the big_brother that will do 1 pipeline
	return only:
		0 on succcess and -1 to exit (for now)
******************************************************************************/
int	ft_father(t_data *data)
{
	t_pipeline	*pipeline;
	int		rtrn;

	pipeline = data->cmd;
	if (!data->cmd)
		return (perror(ERR3"empty args struct"), 1);
	while (pipeline)
	{
		sublim_pipe_v2(data, pipeline);
		rtrn = WEXITSTATUS(data->exit_code);
		if (!pipeline->and_or || (pipeline->and_or == '&' && !rtrn) || (pipeline->and_or == '|' && rtrn))
			rtrn = ft_big_brother_v2(data, pipeline);
		// if (rtrn == 255)
		// 	return (clear_cmd(data), rtrn);
		pipeline = pipeline->next;
	}
	return (clear_cmd(data), 0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		does 1 chained list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
// int	ft_big_brother(t_data *data, t_pipeline *pipeline)
// {
// 	pid_t	pid;
// 	t_cmd	*ptr_cmd;
// 	// int j = 0;

// 	ptr_cmd = pipeline->cmd;
// 	if (brother_builtin(data, ptr_cmd))
// 		ptr_cmd = ptr_cmd->next;
// 	if (!ptr_cmd)
// 		return (0);
// 	pid = fork();
// 	g_pid = pid;
// 	if (pid == -1)
// 		return (perror(ERR7"fork"), 1);
// 	if (!pid)
// 	{
// 		while (ptr_cmd && ptr_cmd->next)
// 		{
// 			if (ft_child(data, ptr_cmd))
// 				end(data, WEXITSTATUS(data->exit_code));
// 			ptr_cmd = ptr_cmd->next;
// 		}
// 		ft_exec(data, ptr_cmd);
// 	}
// 	else
// 	{
// 		// while (waitpid(-1,  &data->exit_code, 0) > 0)
// 		// 	j++;
// 		waitpid(pid, &data->exit_code, 0);
// 	}
// 	return (0);
// }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		takes a cmd node, return the return value of child
		echo a | sleep 5 | echo b
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
// int	ft_child(t_data *data, t_cmd *cmd)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	// int j = 0;

// 	if (pipe(fd) == -1)
// 		return (perror(ERR7"pipe"), 1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (perror(ERR7"fork"), close(fd[0]), close(fd[1]), 2);
// 	if (!pid)
// 	{
// 		close(fd[0]);
// 		dup_close(fd[1], STDOUT);
// 		ft_exec(data, cmd);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup_close(fd[0], STDIN);
// 		// while (waitpid(-1,  &data->exit_code, 0) > 0)
// 		// 	j++;
// 		waitpid(pid, &data->exit_code, 0);
// 	}
// 	return (0);
// }
