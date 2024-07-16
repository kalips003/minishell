/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P_extract_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:28:22 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/16 03:21:02 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_extract_word(char *raw_line, int *i);
char		*ft_extract_words(char *raw_line, int *i);
char		*ft_extract_quotes(char *raw_line, int *i, char quote);
static int	len_m2(char *s, char c);

///////////////////////////////////////////////////////////////////////////////]
// started at the beginning of a word
// return word by spacing
char	*ft_extract_word(char *raw_line, int *i)
{
	int		len;

	if (raw_line[0] == '\'' || raw_line[0] == '"')
		return (ft_extract_quotes(raw_line, i, raw_line[0]));
	len = len_m(raw_line, " \n\t|&<>\"\'");
	*i += len;
	return (str("%1.*s", len, raw_line));
}

// started at the beginning of a word
// return until space
// "      "' sdaf a'"dklfj ;a:'"$ABV
char	*ft_extract_words(char *raw_line, int *i)
{
	int		len;
	char	*rtrn;

	rtrn = NULL;
	len = 0;
	while (raw_line[len])
	{
		if (wii(raw_line[len], " \t\n|&<>") >= 0)
			break ;
		if (raw_line[len] == '\'' || raw_line[len] == '"')
			rtrn = join(rtrn, ft_extract_quotes(raw_line, &len, raw_line[len + 1]), 0b11, 0);
		else
			rtrn = join(rtrn, ft_extract_word(&raw_line[len], &len), 0b11, 0);
	}
	*i += len;
	return (rtrn);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	prend pointer to the beginning of a quote
		> "text"
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
char	*ft_extract_quotes(char *raw_line, int *i, char quote)
{
	char	*rtrn;
	char	*rtrn2;
	int		size;
	int		i_bidon;

	size = len_m2(&raw_line[1], quote) + 2;
	(*i) += size;
	if (size == 2)
		return (NULL);
	rtrn = str("%1.*s", size, raw_line);
	if (rtrn[size - 1] != quote)
	{
		rtrn2 = readline(C_305"finish you quotes: "RESET);
		rtrn = join(rtrn, rtrn2, 0b11, 0);
		rtrn2 = ft_extract_quotes(rtrn, &i_bidon, quote);
		free_s(rtrn);
		(*i)--;
		return (rtrn2);
	}
	return (rtrn);
}

//  return lenght, stops when the char c is found
static int	len_m2(char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
