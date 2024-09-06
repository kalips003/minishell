/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:38:31 by agallon           #+#    #+#             */
/*   Updated: 2024/09/04 12:23:15 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "colors.h"

////////////////////////////////////////////////////////////
//	PRINTF												////
////////////////////////////////////////////////////////////
//	#	STRUCT
typedef struct s_flag
{
	int			minus;
	int			zero;
	int			width;
	int			plus;
	int			space;
	int			hash;
	int			point;
	int			preci;
	char		flag;
	char		error;
	int			increment;
	int			size;
	int			tmp_a;
	long long	num_b;
	char		*rtrn;
	int			fd;
}				t_flags;
//	#
typedef int		(*t_func)(va_list, t_flags *);
typedef char	*(*t_str)(va_list, t_flags *);
//////////////////////////////////////////////////////////////////////////////]
//	#	PRINTF
/// @brief printf with custom flags
/// @param %t [ %.*t ] > put *num \t in front of the tab
/// @param %t [ %-t ] > dont put \\n after each line (for gnl return)
/// @param %t [ %#t ] > dont put \t on first line
/// @param %t [ %+t ] > add char * in front of each line (as second arg)
/// ----------------------------------------------
/// @param %S [ % S ] > spacing, show white space
/// @param %S [ %*S ] > print memory of size *num
/// @param %S [ %.*S ] > add a \\n each sizeof (bit*)
/// @param %S [ %#S ] > hexadecimal
/// @param %S [ %-#S ] > no size 2 precision for hexa (useless)
/// @param %S [ %+S ] > colors +128
int		put(const char *str, ...);
// int		f_1(const char *str, int *i, va_list args);
int		print_fd(int fd, const char *str, ...);
int		ft_print_cat(int num, char *string2, int bit);
////////////////////////////////////////////////////////////
//	#	STRUCT
// static 1
// static 2
void	f_ini_struct(t_flags *flags, int fd);
void	f_error_check(t_flags *flags);
void	f_fill_struct(const char *str, t_flags *f, va_list args);
////////////////////////////////////////////////////////////
//	#	TOOLS
int		ft_strlen666(char *s);
int		atoi_print(const char *str, int *preci_width, t_flags *f, va_list args);
int		size_num_base(long long num, int base);
int		size_float(double nbr, t_flags *flags);
int		size_exp(t_flags *f);
////////////////////////////////////////////////////////////
//	#	TOOLS PRINT
int		wii_print(char c);
int		ft_putnbr_base(int fd, long long nbr, char *base);
int		ft_put_float(double nbr, t_flags *flags);
// static int	ft_put_science_zero(t_flags *f)
int		ft_put_science(double nbr, t_flags *f);
//	#
// static int	is_float(t_flags *f)
// static int	f_prefix_hash(t_flags *f)
int		f_format_num(t_flags *f, long long num, int size_num);
int		size_format_num(long long num, t_flags *flags, int num_size);
int		f_spacing(t_flags *flags, int size);
////////////////////////////////////////////////////////////
//	#	TOOLS UNSIGNED
int		size_format_num_un(unsigned long num, t_flags *f, int num_size);
int		size_num_base_un(unsigned long num, int base);
int		f_format_num_un(t_flags *f, unsigned long num, int size_num);
int		ft_putnbr_base_un(int fd, unsigned long nbr, char *base);
void	*free_333(void *ptr);
//////////////////////////////////////////////////////////////////////////////]
//	#	PRINT FLAG
int		ft_string(va_list args, t_flags *flags);
int		ft_char(va_list args, t_flags *flags);
int		ft_pointer(va_list args, t_flags *flags);
int		ft_int(va_list args, t_flags *flags);
int		ft_unsigned(va_list args, t_flags *flags);
//	#
int		ft_hexa(va_list args, t_flags *flags);
int		ft_percent(va_list args, t_flags *flags);
int		ft_binary(va_list args, t_flags *flags);
int		ft_octal(va_list args, t_flags *flags);
int		ft_float(va_list args, t_flags *flags);
//	#
int		ft_scientific(va_list args, t_flags *flags);
int		ft_string_hexa(va_list args, t_flags *f);
int		ft_tab(va_list args, t_flags *flags);
//////////////////////////////////////////////////////////////////////////////]
//	#	STRING
/// @brief sprintf with custom flags
/// @param %s [ %.*s ] > truncate the string
/// @param %s [ %*s ] > how many time you want to repeat the string
/// @param ! %1s
/// ----------------------------------------------
/// @param %c [ %.*c ] > how many time you want to repeat the char
/// ----------------------------------------------
/// @param %x [ %.*x ] > precise the base as argument
char	*str(char *str, ...);
char	*f_2(char *str, int *i, va_list args);
char	*join(char *begin, char *append, int bit, int size);//  lenght
//	#	STRING FLAGS
char	*pt_string(va_list args, t_flags *f);
char	*pt_char(va_list args, t_flags *f);
char	*pt_num(va_list args, t_flags *f);
char	*pt_hex(va_list args, t_flags *f);

# define MSG_MALLOC "\033[0;31mERROR - MALLOC\n\e[0m"

#endif
