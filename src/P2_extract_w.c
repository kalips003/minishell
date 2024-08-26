/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P2_extract_w.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:28:22 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/26 17:32:43 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		*ft_extract_words_v2(char *raw_line, int *i);
char		*ft_extract_quotes_v2(char *raw_line, int *i, char quote);
static int	len_m2(char *s, char c);

///////////////////////////////////////////////////////////////////////////////]
// started at the beginning of a word
// "      "' sdaf a'"dklfj ;a:'"$ABV

// takes the START of the raw, and work with the &i
// increment i
// stops when find: " \t\n|&<>;"
char	*ft_extract_words_v2(char *raw_line, int *i)
{
	int		len;
	char	*rtrn;

	rtrn = NULL;
	while (raw_line[*i])
	{
		if (wii(raw_line[*i], " \t\n|&<>;") >= 0)
			break ;
		if (raw_line[*i] == '\'' || raw_line[*i] == '"')
			rtrn = join(rtrn, ft_extract_quotes_v2(&raw_line[*i], i, raw_line[*i]), 0b11, 0);
		else
		{
			len = len_m(&raw_line[*i], " \n\t|&<>;\"\'");
			rtrn = join(rtrn, str("%1.*s", len, &raw_line[*i]), 0b11, 0);
			*i += len;
		}
	}
	return (rtrn);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	prend pointer to the beginning of a quote
		> "text
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
char	*ft_extract_quotes_v2(char *raw_line, int *i, char quote)
{
	char	*rtrn;
	char	*rtrn2;
	int		size;
	int		size1;
	int		i_bidon;

	size = wii(quote, &raw_line[1]);
	size1 = len_c(&raw_line[1], quote) + 2 - (size == -1);
	if (size1 == 2)
		return (++(*i), ++(*i), NULL);
	rtrn = str("%1.*s", size1, raw_line);
	if (size == -1)
	{
		(*i) += len(raw_line);
		rtrn2 = readline(C_413"finish your quotes: "RESET);
		rtrn = fjoin(3, 0b101, rtrn, "\n", rtrn2);
		rtrn2 = ft_extract_quotes_v2(rtrn, &i_bidon, quote);
		free_s(rtrn);
		return (rtrn2);
	}
	(*i) += size1;
	return (rtrn);
}

