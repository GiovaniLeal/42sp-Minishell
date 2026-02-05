/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:13:35 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/18 11:44:26 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* ************************************************************************** */
// MEMORY_COPY - copies n bytes from memory area *src to *dest
/* ************************************************************************** */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_bytes;
	const unsigned char	*src_bytes;

	if (!dest && !src && n > 0)
		return (NULL);
	dest_bytes = (unsigned char *)dest;
	src_bytes = (unsigned char *)src;
	while (n--)
	{
		*dest_bytes = *src_bytes;
		src_bytes++;
		dest_bytes++;
	}
	return (dest);
}
