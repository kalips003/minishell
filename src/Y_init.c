/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Y_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 06:21:51 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/27 01:07:13 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			initialization(int ac, char **av, char **env, t_data *data);
static void	copy_env(t_data *data, char **env);
// static void	ini_builtin(t_data *data);
void	handle_sigint(int signal);
void	ini_signal(t_data *data);

pid_t g_pid;

///////////////////////////////////////////////////////////////////////////////]
// ini
int	initialization(int ac, char **av, char **env, t_data *data)
{
	srand(time(NULL));
	ft_memset(data, 0, sizeof(t_data));
	ini_signal(data);
	copy_env(data, env);
	// ini_builtin(data);
	data->fd_in_original = dup(STDIN_FILENO);
	if (ac == 3 && same_str(av[1], "-c"))
	{
		if (ft_parsing_v2(data, av[2]))
			data->exit_code = 0x0100;
		ft_exec_bigbro(data);
		end(data, (WEXITSTATUS(data->exit_code)));
	}
	else if (ac != 1)
		return (put(ERR"Wrong number of arguments\n"), exit(0), 1);
	return (0);
}

static void	copy_env(t_data *data, char **env)
{
	int		i;

	if (!env)
		return ;
	i = -1;
	while (env[++i])
		data->env = expand_tab(data->env, str("%1s", env[i]));
	// data->env = pop_entry(data->env, "SHELL=");
	// data->env = expand_tab(data->env, str("SHELL=%1s/minishell\n", rtrn_var_v2(data->env, "PWD=")));
}

// static void	ini_builtin(t_data *data)
// {
// 	data->builtin_g[0].cmd_name = "cd";
// 	data->builtin_g[0].cmd_exe = cmd_cd;
// 	data->builtin_g[1].cmd_name = "export";
// 	data->builtin_g[1].cmd_exe = cmd_export;
// 	data->builtin_g[2].cmd_name = "unset";
// 	data->builtin_g[2].cmd_exe = cmd_unset;
// 	data->builtin_g[3].cmd_name = "alias";
// 	data->builtin_g[3].cmd_exe = cmd_alias;
// 	data->builtin_g[4].cmd_name = "exit";
// 	data->builtin_g[4].cmd_exe = cmd_exit;
// 	data->builtin[0].cmd_name = "echo";
// 	data->builtin[0].cmd_exe = cmd_echo;
// 	data->builtin[1].cmd_name = "type";
// 	data->builtin[1].cmd_exe = cmd_type;
// 	data->builtin[2].cmd_name = "help";
// 	data->builtin[2].cmd_exe = cmd_help;
// 	data->builtin[3].cmd_name = "miaou";
// 	data->builtin[3].cmd_exe = cmd_miaou;
// }

///////////////////////////////////////////////////////////////////////////////]
// CTRL C = SIGINT
// CTRL \ = SIGQUIT
void handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		kill(g_pid, SIGKILL);
		g_pid = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////]
// 	Function hande signals
void	ini_signal(t_data *data)
{
	data->sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->sig_quit, NULL);
	
	data->sig_int.sa_handler = handle_sigint;
	sigaction(SIGINT, &data->sig_int, NULL);
	
	// data->storeaction.sa_handler = handle_sigint;
	// storeaction.sa_flags = SA_RESTART;
	// sigemptyset(&data->storeaction.sa_mask);
	// sigaddset(&storeaction.sa_mask, SIGINT);
	// signal(SIGINT, handle_sigint);
}