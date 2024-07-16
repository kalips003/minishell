/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:54:09 by kalipso           #+#    #+#             */
/*   Updated: 2024/07/15 21:01:23 by kalipso          ###   ########.fr       */
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





Setting Limits

You can set various limits using ulimit. Here are some common options:

    Core file size (-c): The maximum size of core files created.
    Data segment size (-d): The maximum size of the data segment for a process.
    File size (-f): The maximum size of files created by the shell.
    Number of open files (-n): The maximum number of file descriptors a process can have.
    Stack size (-s): The maximum stack size for a process.
    CPU time (-t): The maximum amount of CPU time a process can use.
    Virtual memory (-v): The maximum amount of virtual memory available to a process.




<?> .PHONY: test - This declares that test is a phony target,
	meaning it's not associated with a file. </?>

// MACRO
// #define funct(ap, type)    (*(type *)((ap += sizeof(type)) - sizeof(type)))
******************************************************************************/
#define PI 3.14159265358979323846
#define BUF_WD 1024
///////////////////////////////////////////////////////////////////////////////]
int	main(int ac, char **av, char **env)
{
	char	**tab = NULL;

	tab = expand_tab(tab, str("a=hello1"));
	tab = expand_tab(tab, str("b=hello2"));
	tab = expand_tab(tab, str("c=hello3"));
	tab = expand_tab(tab, str("d=hello4"));
	put("old:\n%-t", tab);
	tab = pop_entry(tab, "d=");
	put("new:\n%-t", tab);
	tab = pop_entry(tab, "a=");
	put("new:\n%-t", tab);
	// value = sublim_helper2(data, value);
	put(ERR0 ERR1 ERR2 ERR3 ERR4 ERR5 ERR6 ERR7 ERR8 ERR9"PATH=%s=\n", "");
	free_tab(tab);
	return (0);
}
///////////////////////////////////////////////////////////////////////////////]

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
//  			GITHUB
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
git pull
git log > navigate snapshots in time
git log --pretty=fuller
git log --pretty=oneline --abbrev-commit --date=short
git log --since="2022-01-01" --until="2022-12-31"
git checkout <commit-hash>
	Use the hash from the log output.
	save a good commit hash is Makefile Makerestore
To reset the repository to a specific commit:
	git reset --hard <commit-hash>
git push origin feature-branch:main


// Stash Changes: Use git stash to stash your changes.
	git stash
// Switch Branches: After stashing your changes, you can switch branches.
	git checkout <branch-name>
// Apply Stashed Changes: you can apply your stashed changes to the new branch.
	git stash apply
// Pop Stashed Changes: you can apply and remove the stashed changes in one step
	git stash pop
// List Stashes: To see a list of stashed changes, you can use:
	git stash list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
//  			BIWISE
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
while (((condition1) & bit) || ((condition2) & ~bit))

   Setting a Bit at N: (counting from 0)
x |= (1 << N);

   Clearing a Bit at N:
x &= ~(1 << N);

	Toggling a Bit at N:
x ^= (1 << N);

	Toggle a specific range of bits, end (inclusive)
x ^= ((1 << (end - start + 1)) - 1) << start;

	Checking if Bit N is Set:
if (x & (1 << N)) {
	// Bit is set }

	Checking if a Bit is Clear:
if (!(x & (1 << N))) {
	// Bit is clear}

	Setting Multiple Bits at Once:
x |= (1 << 1) | (1 << 3) | (1 << 5);

	Extracting Specific Bits: (3 least)
int	extractedBits = x & 0b111;

	Swapping Two Variables without Using a Temporary Variable:
a ^= b;
b ^= a;
a ^= b;

	Checking if an Integer is Even or Odd: (faster than % 2)
if (num & 1)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

/*
Common flags used with open():

    O_RDONLY: Open for reading only.
    O_WRONLY: Open for writing only.
    O_RDWR: Open for reading and writing.
    O_APPEND: Open in append mode (writes are added to the end of the file).
    O_CREAT: Create the file if it does not exist.
    O_TRUNC: Truncate the file to zero length if it already exists.
*/
