/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:54:09 by kalipso           #+#    #+#             */
/*   Updated: 2024/09/06 14:50:23 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"

/*******************************************************************************
******************************************************************************/
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  </!>
///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************

			░█████╗░  ███████╗░█████╗░██╗██████╗░███████╗
			██╔══██╗  ██╔════╝██╔══██╗██║██╔══██╗██╔════╝
			███████║  █████╗░░███████║██║██████╔╝█████╗░░
			██╔══██║  ██╔══╝░░██╔══██║██║██╔══██╗██╔══╝░░
			██║░░██║  ██║░░░░░██║░░██║██║██║░░██║███████╗
			╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚══════╝


******************************************************************************/

// #define DT_UNKNOWN  0  // Unknown file type
// #define DT_REG      8  // Regular file
// #define DT_DIR      4  // Directory
// #define DT_LNK      10 // Symbolic link

typedef struct s_folder
{
	DIR 		*dir;
	struct dirent *entry;
	char		**all_files;
	char 		*folder_path;
	int			floor;
	struct s_folder **next;

}	t_folder;

t_folder	*new_folder(t_folder *previous, char *folder_path)
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
	folder->entry = 1;
	// folder->entry = readdir(folder->dir);
	while (folder->entry) 
	{
		folder->entry = readdir(folder->dir);
		if (!folder->entry || same_str(folder->entry->d_name, ".") || same_str(folder->entry->d_name, ".."))
			continue;
		folder->all_files = expand_tab(folder->all_files, str("%1s", folder->entry->d_name));
		if (folder->entry->d_type == DT_DIR || folder->entry->d_type == DT_LNK)
		{
			char *full_path = str("%1s/%1s", folder_path, folder->entry->d_name);
			if (!access(full_path, F_OK | R_OK | X_OK))// if 0, access ok
				new_folder(folder, full_path);
			else
				full_path = free_s(full_path);
		}
		// folder->entry = readdir(folder->dir);
	}
	closedir(folder->dir);
	return (folder);
}

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

void	print_folder(t_folder *first)
{
	if (!first)
		return ;
	put(ERR0"FOLDER: %s\n", first->folder_path);
	put("%#-.1t", first->all_files);
	t_folder	(**p_leaf) = first->next;
	if (p_leaf)
	{
		p_leaf = first->next - 1;
		while (*(++p_leaf))
			print_folder(*p_leaf);
	}
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
// 		......../....*
// 		........*..../
int	main(int ac, char **av, char **env)
{
	// t_folder *folder = new_folder(NULL, str("."));
	// print_folder(folder);
	// clean_folder(folder);
	char *pattern = "*ab*cd*f*";
	char *string = "agagagaalkj***ab....cd....f...";
	put("Is Match = %d", f_is_a_match(pattern, string));
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    int pid;

    struct sigaction	sig_int;
    sig_int.sa_sigaction = handle_666;
	sigaction(SIGINT, &sig_int, NULL);
    pid = fork();
    if(!pid)
    {
        int i = 0;
        while (1)
        {
            put("%d\n", i);
            if (sleep(10) == 0)
                exit(0);
            i++;
        }
    }
    pause();
    waitpid(pid, NULL, 0);
    kill(SIGINT, pid);
    put("done\n");

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
