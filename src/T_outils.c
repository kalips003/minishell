/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T_outils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:11:46 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/11 16:42:34 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*trim_white(char *input, char *dico);
void		dup_close(int fd_replace, int fd_erase);

///////////////////////////////////////////////////////////////////////////////]
// trim leading and trailing dico
// free the original
// 	" \n\t"
char	*trim_white(char *input, char *dico)
{
	char	*rtrn;
	char	*start;
	int		lenght;

	if (!input)
		return (NULL);
	start = input;
	while (wii(*start, dico) != -1)
		start++;
	if (!*start)
		return (free_s(input), NULL);
	lenght = len(start);
	while (lenght > 0 && wii(start[lenght - 1], dico) >= 0)
		lenght--;
	rtrn = str("%1.*s", lenght, start);
	free_s(input);
	return (rtrn);
}

///////////////////////////////////////////////////////////////////////////////]
// dup2 and close fd
void	dup_close(int fd_replace, int fd_erase)
{
	if (fd_replace < 0 || fd_erase < 0)
		return ;
	dup2(fd_replace, fd_erase);
	close(fd_replace);
}
