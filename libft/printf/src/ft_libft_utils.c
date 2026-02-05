/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:41:21 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:41:21 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/* STRING FUNCTIONS - CHAR AND STRING HANDLERS                                */
/* ************************************************************************** */
char	*ft_put_char_generic(char c)
{
	char	*buffer;

	buffer = malloc(2);
	if (!buffer)
		return (NULL);
	buffer[0] = c;
	buffer[1] = '\0';
	return (buffer);
}

/* ************************************************************************** */
/*  Generic string handler                                                    */
/* - Returns an allocated copy of the string if do_alloc = 1                  */
/* - Handles NULL strings                                                     */
/* - Does NOT apply precision; it will be handled separately (bonus)         */
/* ************************************************************************** */
char	*ft_put_str_generic(const char *str, int do_alloc)
{
	size_t	len;
	char	*buffer;

	if (!str)
		str = "(null)";
	if (!do_alloc)
		return (ft_strdup(str));
	len = ft_strlen(str);
	buffer = malloc(len + 1);
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, str, len);
	buffer[len] = '\0';
	return (buffer);
}
