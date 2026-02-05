/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:57:07 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/15 17:57:07 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* ************************************************************************** */
/*MEMORY_SET -Fills the first n bytes of memory pointed to s with const byte c*/
/* ************************************************************************** */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_ptr;

	s_ptr = (unsigned char *)s;
	while (n--)
	{
		*s_ptr++ = (unsigned char)c;
	}
	return (s);
}
