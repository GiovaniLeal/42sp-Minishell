/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:53:15 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/28 14:53:15 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
// MEMORY_CHR - Search for c in n bytes of *s
/* ************************************************************************** */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_bytes;
	unsigned char	unsign_char_c;

	s_bytes = (unsigned char *)s;
	unsign_char_c = (unsigned char)c;
	while (n--)
	{
		if (*s_bytes == unsign_char_c)
			return (s_bytes);
		s_bytes++;
	}
	return (NULL);
}
