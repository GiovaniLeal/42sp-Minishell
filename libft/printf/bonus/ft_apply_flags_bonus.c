/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_flag_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:09:46 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/13 14:49:10 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

/* ************************************************************************** */
/* Add a prefix to a string safely                                            */
/* Returns a new allocated string or original if NULL                         */
/* ************************************************************************** */
static char	*ft_add_prefix(char *str, const char *prefix)
{
	char	*res;

	if (!str || !prefix)
		return (str);
	res = ft_strjoin_free(ft_strdup(prefix), str);
	return (res);
}

/* ************************************************************************** */
/* Apply '#' flag for hexadecimal or octal (%x, %X, %o)                       */
/* Returns new allocated string if prefix applied, else original string       */
/* ************************************************************************** */
static char	*ft_apply_flag_hash(char *num_str, t_fmt *fmt)
{
	if (!(fmt->flags & FLAG_HASH))
		return (num_str);
	if ((fmt->specifier == 'x' || fmt->specifier == 'X') && num_str[0] != '0')
	{
		if (fmt->specifier == 'x')
			return (ft_add_prefix(num_str, "0x"));
		else
			return (ft_add_prefix(num_str, "0X"));
	}
	if (fmt->specifier == 'o' && num_str[0] != '0')
		return (ft_add_prefix(num_str, "0"));
	return (num_str);
}

/* ************************************************************************** */
/* Apply '+' or ' ' flag for signed numbers (%d, %i)                          */
/* Returns a new allocated string if flag applied, else original string       */
/* ************************************************************************** */
static char	*ft_apply_flag_sign(char *num_str, t_fmt *fmt)
{
	char	sign;
	char	*res;
	char	tmp[2];

	if ((fmt->specifier != 'd' && fmt->specifier != 'i') || num_str[0] == '-')
		return (num_str);
	sign = 0;
	if (fmt->flags & FLAG_PLUS)
		sign = '+';
	else if (fmt->flags & FLAG_SPACE)
		sign = ' ';
	if (!sign)
		return (num_str);
	tmp[0] = sign;
	tmp[1] = '\0';
	res = ft_strjoin_free(ft_strdup(tmp), num_str);
	return (res);
}

/* ************************************************************************** */
/* Apply all flags in correct order: sign, hash, pointer                      */
/* Returns a new allocated string if any flag applied                         */
/* ************************************************************************** */
char	*ft_apply_flags_bonus(char *str, t_fmt *fmt)
{
	char	*res;

	if (!str || !fmt)
		return (NULL);
	if (fmt->specifier == '%' || (fmt->specifier == 'c' && str[0] == '\0'))
		return (str);
	res = str;
	res = ft_apply_flag_sign(res, fmt);
	if (fmt->specifier != 'p')
		res = ft_apply_flag_hash(res, fmt);
	return (res);
}
