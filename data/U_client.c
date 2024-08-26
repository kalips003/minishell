/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   U_client.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:15:14 by umosse            #+#    #+#             */
/*   Updated: 2024/08/25 18:53:40 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Libft/libft.h"
#include "../inc/minishell.h"



void	send_bit(int index);
void	reception(int sig, siginfo_t *signinfo, void *ptr);
int		minitalk_client(int argc, char *argv[]);

typedef struct s_client{
	int		index;
	char	*str;
	int		size;
	pid_t	pid;
}	t_client;

static struct s_client	g_client;


void	send_bit(int index)
{
	int	bit;

	bit = (g_client.str[index / 8] >> (index % 8)) & 1;
	if (index >= g_client.size * 8)
		return ;
	if (bit == 1)
	{
		kill(g_client.pid, SIGUSR2);
	}
	else if (bit == 0)
	{
		kill(g_client.pid, SIGUSR1);
	}
}

void	reception(int sig, siginfo_t *signinfo, void *ptr)
{
	(void)sig;
	(void)signinfo;
	(void)ptr;
	send_bit(g_client.index);
	g_client.index++;
}

int	minitalk_client(int argc, char *argv[])
{
	struct sigaction	storeaction;

	if (argc == 3)
	{
		storeaction.sa_flags = SA_SIGINFO;
		storeaction.sa_sigaction = (void *)reception;
		sigaction(SIGUSR1, &storeaction, NULL);
		sigaction(SIGUSR2, &storeaction, NULL);
		g_client.pid = atoi_v(argv[1]);
		g_client.str = argv[2];
		g_client.size = len(g_client.str) + 1;
		g_client.index = 1;
		send_bit(0);
		while (g_client.index < g_client.size * 8)
			pause();
	}
	return (0);
}
