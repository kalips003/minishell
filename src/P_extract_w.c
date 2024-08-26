/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P_extract_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:28:22 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/26 19:07:39 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char		*ft_extract_word(char *raw_line, int *i);
// char		*ft_extract_words(char *raw_line, int *i);
// char		*ft_extract_quotes(char *raw_line, int *i, char quote);

// ///////////////////////////////////////////////////////////////////////////////]
// // started at the beginning of a word
// // return word by spacing
// char	*ft_extract_word(char *raw_line, int *i)
// {
// 	int		len;

// 	if (raw_line[0] == '\'' || raw_line[0] == '"')
// 		return (ft_extract_quotes(raw_line, i, raw_line[0]));
// 	len = len_m(raw_line, " \n\t|&<>\"\'");
// 	// put("raw_line =(%s)\n", raw_line);
// 	// put("len = %d\n", len);
// 	*i += len;
// 	return (str("%1.*s", len, raw_line));
// }

// // started at the beginning of a word
// // return until space
// // "      "' sdaf a'"dklfj ;a:'"$ABV
// char	*ft_extract_words(char *raw_line, int *i)
// // {
// // 	int		len;
// // 	int		start = *i;
// // 	char	*rtrn;

// // 	rtrn = NULL;
// // 	len = 0;
// // 	while (raw_line[*i])
// // 	{
// // 		if (wii(raw_line[*i], " \t\n|&<>") >= 0)
// // 			break ;
// // 		if (raw_line[len] == '\'' || raw_line[len] == '"')
// // 			rtrn = join(rtrn, ft_extract_quotes(raw_line, i, raw_line[*i]), 0b11, 0);
// // 		else
// // 			rtrn = join(rtrn, ft_extract_word(&raw_line[len], &len), 0b11, 0);
// // 	}
// // 	*i += len;
// // 	return (rtrn);
// // }
// {
// 	int		len;
// 	char	*rtrn;

// 	rtrn = NULL;
// 	len = 0;
// 	while (raw_line[len])
// 	{
// 		// put("(ft_extract_words) raw_line =(%s)\n", &raw_line[len]);
// 		// put("(ft_extract_words) len = %d\n", len);
// 		if (wii(raw_line[len], " \t\n|&<>;") >= 0)
// 			break ;
// 		if (raw_line[len] == '\'' || raw_line[len] == '"')
// 			rtrn = join(rtrn, ft_extract_quotes(&raw_line[len], &len, raw_line[len]), 0b11, 0);
// 		else
// 			rtrn = join(rtrn, ft_extract_word(&raw_line[len], &len), 0b11, 0);
// 	}
// 	*i += len;
// 	return (rtrn);
// }

// /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// 	prend pointer to the beginning of a quote
// 		> "text
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
// char	*ft_extract_quotes(char *raw_line, int *i, char quote)
// {
// 	char	*rtrn;
// 	char	*rtrn2;
// 	int		size;
// 	int		size1;
// 	int		i_bidon;

// 	size = wii(quote, &raw_line[1]);
// 	size1 = len_c(&raw_line[1], quote) + 2 - (size == -1);
// 	if (size1 == 2)
// 		return (++(*i), ++(*i), NULL);
// 	rtrn = str("%1.*s", size1, raw_line);
// 	// put("(ft_extract_quotes) quote part =(%s)\n", rtrn);
// 	if (size == -1)
// 	{
// 		(*i) += len(raw_line);
// 		rtrn2 = readline(C_234"finish you quotes: "RESET);
// 		rtrn = join(rtrn, rtrn2, 0b11, 0);
// 		rtrn2 = ft_extract_quotes(rtrn, &i_bidon, quote);
// 		free_s(rtrn);
// 		return (rtrn2);
// 	}
// 	(*i) += size1;
// 	return (rtrn);
// }
// // {
// // 	char	*rtrn;
// // 	char	*rtrn2;
// // 	int		size;
// // 	int		size1;
// // 	int		i_bidon;

// // 	rtrn = NULL;
// // 	size1 = len_m2(&raw_line[1], quote) + 1;
// // 	size = wii(quote, &raw_line[1]) + 2;
// // 	if (size == 2)
// // 		return (++(*i), ++(*i), NULL);
// // 	rtrn = str("%1.*s", size1, raw_line);
// // 	if (size == 1)
// // 	{
// // 		(*i) += len(raw_line);
// // 		rtrn2 = readline(C_234"finish you quotes: "RESET);
// // 		rtrn = join(rtrn, rtrn2, 0b11, 0);
// // 		rtrn2 = ft_extract_quotes(rtrn, &i_bidon, quote);
// // 		free_s(rtrn);
// // 		return (rtrn2);
// // 	}
// // 	(*i) += size;
// // 	return (rtrn);
// // }
// // {
// // 	char	*rtrn;
// // 	char	*rtrn2;
// // 	int		size;
// // 	int		i_bidon;

// // 	size = len_m2(&raw_line[1], quote) + 2;
// // 	// size = wii(quote, &raw_line[1]);
// // 	(*i) += size;
// // 	if (size == 2)
// // 		return (NULL);
// // 	rtrn = str("%1.*s", size, raw_line);
// // 	if (rtrn[size - 1] != quote)
// // 	{
// // 		rtrn2 = readline(C_305"finish you quotes: "RESET);
// // 		rtrn2 = join(rtrn2, "\n", 0b10, 0);
// // 		rtrn = join(rtrn, rtrn2, 0b11, 0);
// // 		rtrn2 = ft_extract_quotes(rtrn, &i_bidon, quote);
// // 		free_s(rtrn);
// // 		(*i)--;
// // 		return (rtrn2);
// // 	}
// // 	return (rtrn);
// // }
