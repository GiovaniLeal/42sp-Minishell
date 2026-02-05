/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_width_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:12:53 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/13 15:14:26 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

/* ************************************************************************** */
/*   Returns padding char: '0' or ' '                                         */
/*   - '0' is ignored if '-' flag or precision is set                         */
/* ************************************************************************** */
static char	ft_get_fill_char(t_fmt *fmt, int is_number)
{
	if ((fmt->flags & FLAG_ZERO) && !(fmt->flags & FLAG_MINUS)
		&& is_number && !fmt->precision_specified)
		return ('0');
	return (' ');
}

/* ************************************************************************** */
/*   Returns prefix length preserved during zero-padding                      */
/*   - Handles sign (+, -, space) and 0x / 0X for hex and pointers            */
/* ************************************************************************** */
static size_t	ft_get_prefix_len(char *str, t_fmt *fmt, char fill)
{
	size_t	len;

	len = 0;
	if (fill == '0')
	{
		if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
			len = 1;
		else if ((fmt->specifier == 'x' || fmt->specifier == 'X'
				|| fmt->specifier == 'p')
			&& str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
			len = 2;
	}
	return (len);
}

/* ************************************************************************** */
/*   Applies left alignment with space padding                                */
/* ************************************************************************** */
static void	ft_apply_left(char *res, char *str, size_t str_len, size_t pad_len)
{
	ft_memcpy(res, str, str_len);
	ft_memset(res + str_len, ' ', pad_len);
}

/* ************************************************************************** */
/*   Applies right alignment with correct padding                             */
/*   - Handles zero-padding and prefix preservation                           */
/* ************************************************************************** */
static void	ft_apply_right(char *res, char *str, t_fmt *fmt, size_t str_len)
{
	char	fill;
	size_t	pad_len;
	size_t	prefix_len;

	pad_len = fmt->width - str_len;
	fill = ft_get_fill_char(fmt, (fmt->specifier == 'd' || fmt->specifier == 'i'
				|| fmt->specifier == 'u' || fmt->specifier == 'x'
				|| fmt->specifier == 'X' || fmt->specifier == 'p'));
	prefix_len = ft_get_prefix_len(str, fmt, fill);
	if (fill == '0' && prefix_len > 0)
	{
		ft_memcpy(res, str, prefix_len);
		ft_memset(res + prefix_len, '0', pad_len);
		ft_memcpy(res + prefix_len + pad_len,
			str + prefix_len, str_len - prefix_len);
	}
	else
	{
		ft_memset(res, fill, pad_len);
		ft_memcpy(res + pad_len, str, str_len);
	}
}

/* ************************************************************************** */
/*   Applies width to formatted string                                        */
/*   - Allocates new buffer if width > string length                          */
/*   - Handles left/right alignment and null char for %c                      */
/* ************************************************************************** */
char	*ft_apply_width_bonus(char *str, t_fmt *fmt)
{
	char	*res;
	size_t	str_len;
	size_t	pad_len;
	int		is_null_char;

	is_null_char = (fmt->specifier == 'c' && str[0] == '\0');
	if (is_null_char)
		str_len = 1;
	else
		str_len = ft_strlen(str);
	if ((size_t)fmt->width <= str_len)
		return (str);
	pad_len = fmt->width - str_len;
	res = malloc(fmt->width + 1);
	if (!res)
		return (ft_strdup(str));
	if (fmt->flags & FLAG_MINUS)
		ft_apply_left(res, str, str_len, pad_len);
	else
		ft_apply_right(res, str, fmt, str_len);
	res[fmt->width] = '\0';
	return (res);
}
