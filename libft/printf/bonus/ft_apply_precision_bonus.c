/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_precision_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:16:29 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/13 13:35:12 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

/* ************************************************************************** */
/* Fill numeric string according to precision                                 */
/* Allocates memory and inserts leading zeros                                 */
/* ************************************************************************** */
static char	*ft_numeric_precision_fill(char *num_str, t_fmt *fmt,
	int num_len, int is_negative)
{
	char	*res;
	int		total_len;
	int		i;

	total_len = fmt->precision + is_negative;
	res = malloc(total_len + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (is_negative)
	{
		res[0] = '-';
		i = 1;
	}
	ft_memset(res + i, '0', fmt->precision - num_len);
	ft_memcpy(res + i + (fmt->precision - num_len),
		num_str + is_negative, num_len);
	res[total_len] = '\0';
	return (res);
}

/* ************************************************************************** */
/* Calculate numeric precision length and handle special zero case            */
/* Returns allocated string if zero with precision 0, else NULL               */
/* ************************************************************************** */
static char	*ft_numeric_precision_len(char *num_str, t_fmt *fmt,
	int *num_len, int *is_negative)
{
	*is_negative = (num_str[0] == '-');
	if (num_str[*is_negative] == '0' && num_str[*is_negative + 1] == '\0'
		&& fmt->precision_specified && fmt->precision == 0)
		return (ft_strdup(""));
	*num_len = ft_strlen(num_str) - *is_negative;
	if (!fmt->precision_specified || *num_len >= fmt->precision)
		return (ft_strdup(num_str));
	return (NULL);
}

/* ************************************************************************** */
/* Core function: apply precision to numeric string                           */
/* Uses helper functions above to limit variables and lines                   */
/* ************************************************************************** */
char	*ft_apply_precision_num(char *num_str, t_fmt *fmt)
{
	char	*res;
	int		num_len;
	int		is_negative;

	res = ft_numeric_precision_len(num_str, fmt, &num_len, &is_negative);
	if (res != NULL)
		return (res);
	return (ft_numeric_precision_fill(num_str, fmt, num_len, is_negative));
}

/* ************************************************************************** */
/*   Apply precision for strings                                              */
/*   - Handles normal strings and NULL                                        */
/*   -For NULL, behaves like printf: "(null)" truncated according to precision*/
/* ************************************************************************** */
char	*ft_apply_precision_str(char *str, t_fmt *fmt)
{
	size_t	str_len;
	size_t	prec_len;

	str_len = ft_strlen(str);
	if (fmt->precision_specified)
	{
		prec_len = fmt->precision;
		if (ft_strcmp(str, "(null)") == 0 && fmt->precision < 1)
		{
			if (prec_len == 0)
				return (ft_strdup(""));
			prec_len++;
		}
		if (prec_len < str_len)
			return (ft_substr(str, 0, prec_len));
	}
	return (ft_strdup(str));
}

/* ************************************************************************** */
/* Apply precision for pointer (%p)                                           */
/* Returns allocated string or NULL on allocation failure                     */
/* Special case: 0 pointer with precision 0 returns empty string              */
/* ************************************************************************** */
char	*ft_apply_precision_ptr(char *ptr_str, t_fmt *fmt)
{
	char	*res;

	if (!ptr_str)
		res = ft_strdup("0x0");
	else
		res = ft_strdup(ptr_str);
	if (!res)
		return (NULL);
	if (ft_strcmp(res, "0x0") == 0 && fmt->precision_specified
		&& fmt->precision == 0)
	{
		free(res);
		res = ft_strdup("");
	}
	return (res);
}
