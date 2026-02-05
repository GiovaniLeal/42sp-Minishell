/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:52:05 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/13 17:05:45 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

/* *************************************************************** */
/*   Initialize format struct                                      */
/*   - Reset all fields to default values                          */
/*   - Ensures no garbage values remain                            */
/* *************************************************************** */
static void	ft_init_format(t_fmt *f)
{
	f->flags = 0;
	f->width = 0;
	f->precision = -1;
	f->precision_specified = 0;
	f->specifier = 0;
}

/* *************************************************************** */
/*   Parse flags                                                   */
/*   - Recognizes '-', '+', ' ', '#', '0'                          */
/*   - Updates flags bitmask in format struct                      */
/*   - Resolves conflicts:                                         */
/*       '-' overrides '0'                                         */
/*       '+' overrides ' '                                         */
/* *************************************************************** */
static void	ft_parse_flags(const char **fmt, t_fmt *f)
{
	while (**fmt == '-' || **fmt == '+' || **fmt == ' '
		|| **fmt == '#' || **fmt == '0')
	{
		if (**fmt == '-')
			f->flags |= FLAG_MINUS;
		else if (**fmt == '+')
			f->flags |= FLAG_PLUS;
		else if (**fmt == ' ')
			f->flags |= FLAG_SPACE;
		else if (**fmt == '#')
			f->flags |= FLAG_HASH;
		else if (**fmt == '0')
			f->flags |= FLAG_ZERO;
		(*fmt)++;
	}
	if (f->flags & FLAG_MINUS)
		f->flags &= ~FLAG_ZERO;
	if (f->flags & FLAG_PLUS)
		f->flags &= ~FLAG_SPACE;
}

/* *************************************************************** */
/*   Parse width                                                   */
/*   - Handles fixed width (digits)                                */
/*   - Handles dynamic width ('*' argument)                        */
/* *************************************************************** */
static void	ft_parse_width(const char **fmt, t_fmt *f, va_list args)
{
	if (**fmt == '*')
	{
		f->width = va_arg(args, int);
		(*fmt)++;
	}
	else
	{
		f->width = 0;
		while (**fmt >= '0' && **fmt <= '9')
			f->width = f->width * 10 + (*(*fmt)++ - '0');
	}
}

/* *************************************************************** */
/*   Parse precision                                               */
/*   - Handles precision specifier starting with '.'               */
/*   - Supports '*' for dynamic precision                          */
/*   - Stores precision value and marks as specified               */
/* *************************************************************** */
static void	ft_parse_precision(const char **fmt, t_fmt *f, va_list args)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		f->precision_specified = 1;
		if (**fmt == '*')
		{
			f->precision = va_arg(args, int);
			(*fmt)++;
		}
		else
		{
			f->precision = 0;
			while (**fmt >= '0' && **fmt <= '9')
				f->precision = f->precision * 10 + (*(*fmt)++ - '0');
		}
	}
}

/* *************************************************************** */
/*   Parse full format specifier                                   */
/*   - Initializes format struct                                   */
/*   - Parses flags, width, precision, and specifier               */
/*   - Advances format pointer                                     */
/* *************************************************************** */
void	ft_parse_format_bonus(const char **format_ptr,
		t_fmt *f, va_list args)
{
	ft_init_format(f);
	ft_parse_flags(format_ptr, f);
	ft_parse_width(format_ptr, f, args);
	ft_parse_precision(format_ptr, f, args);
	if (**format_ptr)
		f->specifier = *(*format_ptr)++;
}
