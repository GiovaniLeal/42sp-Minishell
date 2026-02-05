/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_strg_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:32:54 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/14 22:32:54 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"
/* ************************************************************************** */
/*   Returns a string for %c or %%                                          */
/*   - Allocates a buffer to store the character                              */
/*   - Handles null character '\0' properly for width/flags                  */
/* ************************************************************************** */
char	*ft_put_char_printf(char c, int is_percent)
{
	char	*buffer;

	(void)is_percent;
	buffer = malloc(2);
	if (!buffer)
		return (NULL);
	buffer[0] = c;
	buffer[1] = '\0';
	return (buffer);
}

/* ************************************************************************** */
/*   Format string with bonus rules                                           */
/*   - Applies precision, then flags, then width                              */
/*   - Frees intermediate strings to avoid leaks                              */
/* ************************************************************************** */
char	*ft_put_str_printf(const char *str)
{
	char	*buffer;
	size_t	len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	buffer = malloc(len + 1);
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, str, len);
	buffer[len] = '\0';
	return (buffer);
}
