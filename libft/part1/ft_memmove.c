/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:43:47 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/18 12:00:44 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* ************************************************************************** */
/* MEMORY_MOVE - copies n bytes from src to dest.Valide src and dest size     */
/* ************************************************************************** */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_byte;
	unsigned char	*src_byte;

	dest_byte = (unsigned char *)dest;
	src_byte = (unsigned char *)src;
	if (dest_byte < src_byte)
	{
		while (n--)
		{
			*dest_byte++ = *src_byte++;
		}
	}
	else if (dest_byte > src_byte)
	{
		while (n--)
		{
			dest_byte[n] = src_byte[n];
		}
	}
	return ((void *)dest);
}
