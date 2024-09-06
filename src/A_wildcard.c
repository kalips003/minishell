/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_wildcard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:29:53 by kalipso           #+#    #+#             */
/*   Updated: 2024/09/06 14:49:18 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		sublim_pipe_v2(t_data *data, t_pipeline *pipe);

void	sublim_wildcard(t_cmd *cmd);
char	**cut_pattern(char *pattern);
t_folder	*new_folder_wildcard(t_folder *previous, char *folder_path, char **pattern);
static void	h_new_folder_wildcard(t_folder *folder, char **pattern);
char	**return_all_match(t_folder *first);
void	*clean_folder(t_folder *first);
int	is_a_match(char *pattern, char *string);
char	**expand_tab_tab(char **input, char **to_add, int bit);

///////////////////////////////////////////////////////////////////////////////]

typedef struct s_folder
{
	DIR 		*dir;
	struct dirent *entry;
	char		**all_files;
	char 		*folder_path;
	int			floor;
	char 		*pattern_to_match;
	struct s_folder **next;

}	t_folder;

///////////////////////////////////////////////////////////////////////////////]
// recieve: args = {echo, */*.c, -abc} > {echo, lib/file.c, .. src/f2.c, -abc}
void	sublim_wildcard(t_cmd *cmd)
{
	char (**rtrn) = NULL;
	int	(i) = -1;
	if(!cmd->cmd_arg)
		return ;
	while (*cmd->cmd_arg[++i])
	{
		if (wii('*', cmd->cmd_arg[i]) >= 0)
		{
			char **pattern = cut_pattern(*cmd->cmd_arg[i]);
			t_folder *folder = new_folder_wildcard(NULL, str("."), pattern);
			rtrn = expand_tab_tab(rtrn, return_all_match(folder), 0b11);
			clean_folder(folder);
			free_tab(pattern);
		}
	}
	free_tab(cmd->cmd_arg);
	cmd->cmd_arg = rtrn;
}

///////////////////////////////////////////////////////////////////////////////]
/// cut */*/*.c
// 	abc/hello/de*f/ghi.* > {abc, hello, les, ami, de*f, ghi.*}
// cut the path arg:
// 		 path/*/to_some*/file/that/may/exist/m*a*y*b*e.*
// return un tableau avec les folders qui contiennent des * separe:
// 		> {path, *, to_some*, file/that/may/exist, m*a*y*b*e.*}
char	**cut_pattern(char *pattern)
{

	char	(**rtrn) = split(pattern, "/");
	int (i) = -1;

	if (!rtrn)
		return (NULL);
	if (*pattern == '/');
		rtrn[0] = join("/", rtrn[0], 0b01, 0);
	while (rtrn[++i])
	{
		if (wii('*', rtrn[i]) >= 0)
			continue ;
		else if (wii('*', rtrn[i + 1]) == -1)
		{
			rtrn[i] = fjoin(3, 0b100, rtrn[i], "/", rtrn[i + 1]);
			rtrn = pop_tab(rtrn, rtrn[i + 1]);
			i--;
		}
	}
	return (rtrn);
}


///////////////////////////////////////////////////////////////////////////////]
// create a new node, fill it with file & folder that match the n-th pattern
// path to match == pattern[folder->floor]
t_folder	*new_folder_wildcard(t_folder *previous, char *folder_path, char **pattern)
{
	t_folder	(*folder) = (t_folder *)mem(0, sizeof(t_folder));
	if (!folder)
		return (NULL);
	if (previous)
	{
		folder->floor = previous->next + 1;
		previous->next = (t_folder **)expand_tab((char **)previous->next, (char *)folder);
	}
	folder->folder_path = folder_path;// malloccd
	folder->dir = opendir(folder_path);
	if (!folder->dir)
		return (perror("opendir"), NULL);
	folder->pattern_to_match = pattern[folder->floor];
	h_new_folder_wildcard(folder, pattern);
	closedir(folder->dir);
	return (folder);
}

static void	h_new_folder_wildcard(t_folder *folder, char **pattern)
{
	char *full_path;
	
	folder->entry = 1;
	while (folder->entry) 
	{
		folder->entry = readdir(folder->dir);
		if (!folder->entry || 
				same_str(folder->entry->d_name, ".") || 
				same_str(folder->entry->d_name, "..") || 
				(folder->entry->d_name[0] == '.' && folder->pattern_to_match[0] != '.') ||
				!is_a_match(folder->pattern_to_match, folder->entry->d_name))
			continue;
		folder->all_files = expand_tab(folder->all_files, str("%1s", folder->entry->d_name));
		if (pattern[folder->floor + 1] && (folder->entry->d_type == DT_DIR || folder->entry->d_type == DT_LNK))
		{
			full_path = str("%1s/%1s", folder->folder_path, folder->entry->d_name);
			if (!access(full_path, F_OK | R_OK | X_OK))
				new_folder_wildcard(folder, full_path, pattern);
			else
				full_path = free_s(full_path);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// return the tab of all files with matching name
char	**return_all_match(t_folder *first)
{
	char		(**rtrn) = NULL;
	t_folder	**p_leaf;
	
	if (!first)
		return (NULL);
	p_leaf = first->next;
	if (p_leaf)
	{
		p_leaf = first->next - 1;
		while (*(++p_leaf))
			rtrn = expand_tab_tab(rtrn, return_all_match(*p_leaf), 0b11);
	}
	else
	{
		rtrn = first->all_files;
		first->all_files = NULL;
	}
	return (rtrn);
}

///////////////////////////////////////////////////////////////////////////////]
// free tree folders
void	*clean_folder(t_folder *first)
{
	if (!first)
		return (NULL);
	free_tab(first->all_files);
	free_s(first->folder_path);
	t_folder	(**p_leaf) = first->next;
	if (p_leaf)
	{
		p_leaf = first->next - 1;
		while (*(++p_leaf))
			clean_folder(*p_leaf);
	}
	free_s(first->next);
	free_s(first);
	return (NULL);
}

///////////////////////////////////////////////////////////////////////////////]
/// return 1 if is a match, 0 if not
/// we match 'ab*cd*f*' with each file in current directory 'ab....cd....f...'
// 		'a*b' > 'a..................b'
int	is_a_match(char *pattern, char *string)
{
	if (!pattern || !string)
		return (pattern == string);
	if (!*pattern && !*string)
		return (1);
	if (*pattern == '*')
		return (is_a_match(pattern + 1, string) || (*string && is_a_match(pattern, string + 1)));
	if (*pattern == *string)
		return (is_a_match(pattern + 1, string + 1));
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/// if 0b10, free input
/// if 0b01, free to_add
char	**expand_tab_tab(char **input, char **to_add, int bit)
{
	char	(**ptr) = input;
	char	(**rtrn) = NULL;
	if (!input || !to_add)
		return ((char **)((size_t)input + (size_t)to_add));
	if (ptr && ptr--)
		while (*(++ptr))
			rtrn = expand_tab(rtrn, *ptr);
	ptr = to_add;
	if (ptr && ptr--)
		while (*(++ptr))
			rtrn = expand_tab(rtrn, *ptr);
	if (bit & 1)
		free_s(to_add);
	if (bit >> 1 & 1)
		free_s(input);
	return (rtrn);
}
