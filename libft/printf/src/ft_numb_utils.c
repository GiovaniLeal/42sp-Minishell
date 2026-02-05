/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numb_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:44:47 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:44:47 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/* DECIMAL NUMBERS - CONVERTS DECIMAL OR UNSIGNED TO STRING                   */
/* ************************************************************************** */
char	*ft_put_num(char specifier, long long number)
{
	if (specifier == 'u')
		return (ft_utoa_base((unsigned long long)number, BASE_DEC));
	return (ft_itoa_base(number, BASE_DEC));
}

/* ************************************************************************** */
/* HEXADECIMAL - CONVERTS UNSIGNED INT TO HEX STRING (LOWER/UPPER)            */
/* ************************************************************************** */
char	*ft_put_hex(char specifier, unsigned int number)
{
	if (specifier == 'x')
		return (ft_utoa_base((unsigned long long)number, BASE_HEX));
	return (ft_utoa_base((unsigned long long)number, BASE_HEX_UPP));
}

/* ************************************************************************** */
/* POINTER - CONVERTS POINTER TO HEX STRING WITH '0x' PREFIX                  */
/* ************************************************************************** */
char	*ft_put_ptr(void *ptr)
{
	char				*hex_str;
	char				*new_str;
	size_t				hex_len;
	unsigned long long	addr_val;

	if (!ptr)
		return (ft_strdup("(nil)"));
	addr_val = (unsigned long long)ptr;
	hex_str = ft_utoa_base(addr_val, BASE_HEX);
	if (!hex_str)
		return (NULL);
	hex_len = ft_strlen(hex_str);
	new_str = malloc(hex_len + 3);
	if (!new_str)
	{
		free(hex_str);
		return (NULL);
	}
	new_str[0] = '0';
	new_str[1] = 'x';
	ft_memcpy(new_str + 2, hex_str, hex_len);
	new_str[hex_len + 2] = '\0';
	free(hex_str);
	return (new_str);
}

/* ************************************************************************** */
/* UTOA BASE - CONVERTS UNSIGNED LONG LONG TO STRING IN GIVEN BASE            */
/* ************************************************************************** */
char	*ft_utoa_base(unsigned long long value, const char *base)
{
	char	buffer[65];
	int		base_len;
	int		i;
	char	*new_str;

	base_len = ft_strlen(base);
	if (base_len < 2)
		return (NULL);
	if (value == 0)
		return (ft_strdup("0"));
	i = 64;
	buffer[i] = '\0';
	while (value > 0)
	{
		buffer[--i] = base[value % base_len];
		value /= base_len;
	}
	new_str = ft_strdup(&buffer[i]);
	return (new_str);
}

/* ************************************************************************** */
/* ITOA BASE - CONVERTS SIGNED LONG LONG TO STRING IN GIVEN BASE              */
/* ************************************************************************** */
char	*ft_itoa_base(long long value, const char *base)
{
	char				buffer[65];
	int					base_len;
	int					i;
	unsigned long long	abs_val;

	base_len = ft_strlen(base);
	if (base_len < 2)
		return (NULL);
	i = 64;
	buffer[i--] = '\0';
	if (value < 0)
		abs_val = -(unsigned long long)value;
	else
		abs_val = value;
	if (abs_val == 0)
		buffer[i--] = '0';
	while (abs_val > 0)
	{
		buffer[i--] = base[abs_val % base_len];
		abs_val /= base_len;
	}
	if (value < 0)
		buffer[i--] = '-';
	return (ft_strdup(&buffer[i + 1]));
}
