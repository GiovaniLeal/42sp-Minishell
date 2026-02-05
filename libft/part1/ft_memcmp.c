/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:18:50 by marvin            #+#    #+#             */
/*   Updated: 2025/07/18 23:18:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
// MEMORY COMPARE - compares the first n bytes of the memory areas s1 and s2
/* ************************************************************************** */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_byte;
	unsigned char	*s2_byte;

	s1_byte = (unsigned char *)s1;
	s2_byte = (unsigned char *)s2;
	while (n--)
	{
		if (*s1_byte != *s2_byte)
		{
			return (*s1_byte - *s2_byte);
		}
		s2_byte++;
		s1_byte++;
	}
	return (0);
}
