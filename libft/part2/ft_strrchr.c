/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:17:10 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/18 18:08:04 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
//Returns a pointer to the last occurrence of character c in string s, or NULL.
/* ************************************************************************** */
char	*ft_strrchr(const char *s, int c)
{
	char			*s_bytes;
	int				index;
	unsigned char	uc;

	index = ft_strlen(s);
	s_bytes = (char *)s;
	uc = (unsigned char)c;
	while (index >= 0)
	{
		if (s_bytes[index] == uc)
			return (&s_bytes[index]);
		index--;
	}
	return (NULL);
}
