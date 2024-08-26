/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_builtin_tools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:28:22 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/26 19:30:17 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	replace_var(t_data *data, char *to_replace, char *replacement);
char	**pop_entry(char **env, char *to_pop);

///////////////////////////////////////////////////////////////////////////////]
// replace the entry in the env tab
// void	replace_vr2(char **env, char *"CWD=", char *(m)"CWD=this/is/new/cwd");
void	replace_var(t_data *data, char *var, char *replacement)
{
	if (!replacement || !data->env)
		return ;
	if (!rtrn_var_v2(data->env, var) && replacement)
		data->env = expand_tab(data->env, replacement);
	else
	{
		data->env = pop_entry(data->env, var);
		data->env = expand_tab(data->env, replacement);
	}
}

// pop the line: "CWD=..."
// free old tab; return ptr to new tab
char	**pop_entry(char **env, char *to_pop)
{
	char	**new_tab;
	char	**tab_ptr;

	if (!env || !to_pop)
		return (env);
	new_tab = NULL;
	tab_ptr = env - 1;
	while (*(++tab_ptr))
	{
		if (*tab_ptr[0] == to_pop[0] && !find_str(*tab_ptr, to_pop))
		{
			free_s(*tab_ptr);
			continue ;
		}
		new_tab = expand_tab(new_tab, *tab_ptr);
	}
	free_s(env);
	return (new_tab);
}

