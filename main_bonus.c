/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:03 by marvin            #+#    #+#             */
/*   Updated: 2024/08/09 16:01:16 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///////////////////////////////////////////////////////////////////////////////]
int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		rtrn;

	initialization(ac, av, env, &data);
	while (1)
	{
		rtrn = ft_minishell(&data);
		if (WEXITSTATUS(rtrn) == 255)
			break ;
	}
	end(&data, 0);
	return (0);
}
