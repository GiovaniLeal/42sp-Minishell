/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:57:47 by giodos-s          #+#    #+#             */
/*   Updated: 2025/11/03 18:56:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* BYTE_ZERO = Erase data in the n bytes of the memory                        */
/* ************************************************************************** */
void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	size_t			*long_ptr;
	unsigned char	*byte_ptr;

	i = 0;
	long_ptr = (size_t *)s;
	while (n >= sizeof(size_t))
	{
		long_ptr[i++] = 0;
		n -= sizeof(size_t);
	}
	byte_ptr = (unsigned char *)&long_ptr[i];
	while (n--)
		*byte_ptr++ = 0;
	return (s);
}
