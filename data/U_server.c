/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   U_server.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:15:11 by umosse            #+#    #+#             */
/*   Updated: 2024/08/25 18:54:07 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Printf/ft_printf.h"
// #include "Libft/libft.h"

#include "../inc/minishell.h"


char	*my_realloc(char *src);
void	receivesign(int sig, siginfo_t *signinfo, void *ptr);
int	minitalk_server(void);

typedef struct s_server{
	char	c;
	int		index;
	char	*buffer;
	int		buffer_index;
	int		buffer_size;
	pid_t	pid;
}	t_server;

static t_server	g_srv;

///////////////////////////////////////////////////////////////////////////////]
static void	*ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = str;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return (str);
}

///////////////////////////////////////////////////////////////////////////////]
char	*my_realloc(char *src)
{
	char	*dest;
	int		j;

	j = 0;
	dest = malloc(g_srv.buffer_size + 256);
	if (!dest)
		return (NULL);
	if (src != NULL)
	{
		while (j < g_srv.buffer_size)
		{
			dest[j] = src[j];
			j++;
		}
		free(src);
	}
	g_srv.buffer_size += 256;
	return (dest);
}

void	receivesign(int sig, siginfo_t *signinfo, void *ptr)
{
	(void)ptr;
	if (g_srv.buffer_index >= g_srv.buffer_size - 1)
		g_srv.buffer = my_realloc(g_srv.buffer);
	g_srv.pid = signinfo->si_pid;
	if (sig == SIGUSR2)
		g_srv.c = g_srv.c | (1 << g_srv.index);
	g_srv.index++;
	if (g_srv.index == 8)
	{
		g_srv.buffer[g_srv.buffer_index++] = g_srv.c;
		if (g_srv.c == '\0')
		{
			printf("%s\n", g_srv.buffer);
			g_srv.buffer_index = 0;
			free(g_srv.buffer);
			g_srv.buffer = NULL;
			g_srv.buffer_size = 0;
		}
		g_srv.c = 0;
		g_srv.index = 0;
	}
	kill(signinfo->si_pid, SIGUSR1);
}

int	minitalk_server(void)
{
	struct sigaction	storeaction;

	put("%d\n", getpid());
	ft_bzero(&storeaction, sizeof(struct sigaction));
	storeaction.sa_flags = SA_SIGINFO;
	storeaction.sa_sigaction = (void *) receivesign;
	sigaction(SIGUSR1, &storeaction, NULL);
	sigaction(SIGUSR2, &storeaction, NULL);
	g_srv.c = 0;
	g_srv.index = 0;
	g_srv.buffer = NULL;
	g_srv.buffer_index = 0;
	g_srv.buffer_size = 0;
	while (1)
		pause();
	free(g_srv.buffer);
	return (0);
}
