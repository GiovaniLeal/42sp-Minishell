/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatcher_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:00:08 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/13 11:40:00 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

/* ************************************************************************** */
/*   Apply precision                                                          */
/*   - For '%' and null char 'c', ignore precision                            */
/*   - Otherwise, delegate by specifier                                       */
/* ************************************************************************** */
static char	*ft_apply_precision_bonus(char *str, t_fmt *f)
{
	if (f->specifier == '%' || (f->specifier == 'c' && str[0] == '\0'))
		return (str);
	if (f->specifier == 's')
		return (ft_apply_precision_str(str, f));
	else if (f->specifier == 'p')
		return (ft_apply_precision_ptr(str, f));
	else if (f->specifier == 'd' || f->specifier == 'i'
		|| f->specifier == 'u' || f->specifier == 'x'
		|| f->specifier == 'X')
		return (ft_apply_precision_num(str, f));
	return (str);
}

/* ************************************************************************** */
/*   Format bonus string                                                      */
/*   - Applies precision, flags, width in correct order                       */
/*   - Handles NULL strings safely                                            */
/* ************************************************************************** */
char	*ft_format_bonus(char *raw_str, t_fmt *fmt)
{
	char	*tmp;

	if (!raw_str || !fmt)
		return (NULL);
	tmp = ft_apply_precision_bonus(raw_str, fmt);
	if (tmp != raw_str)
		free(raw_str);
	raw_str = tmp;
	tmp = ft_apply_flags_bonus(raw_str, fmt);
	if (tmp != raw_str)
		free(raw_str);
	raw_str = tmp;
	tmp = ft_apply_width_bonus(raw_str, fmt);
	if (tmp != raw_str)
		free(raw_str);
	raw_str = tmp;
	return (raw_str);
}

/* ************************************************************************** */
/*   Dispatcher for bonus specifiers                                          */
/*   - Converts argument and applies formatting                               */
/* ************************************************************************** */
char	*ft_dispatcher_bonus(t_fmt *fmt, va_list args)
{
	char	*raw_str;

	if (!fmt)
		return (NULL);
	raw_str = NULL;
	if (fmt->specifier == 'c')
		raw_str = ft_put_char_printf((char)va_arg(args, int), 0);
	else if (fmt->specifier == '%')
		raw_str = ft_put_char_printf('%', 1);
	else if (fmt->specifier == 's')
		raw_str = ft_put_str_printf(va_arg(args, char *));
	else if (fmt->specifier == 'd' || fmt->specifier == 'i')
		raw_str = ft_put_num(fmt->specifier, va_arg(args, int));
	else if (fmt->specifier == 'u')
		raw_str = ft_put_num(fmt->specifier, va_arg(args, unsigned int));
	else if (fmt->specifier == 'x' || fmt->specifier == 'X')
		raw_str = ft_put_hex(fmt->specifier, va_arg(args, unsigned int));
	else if (fmt->specifier == 'p')
		raw_str = ft_put_ptr(va_arg(args, void *));
	else
		return (NULL);
	return (ft_format_bonus(raw_str, fmt));
}
