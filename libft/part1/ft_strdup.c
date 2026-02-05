/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:06:27 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/21 19:06:27 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* STRING_DUPLICATE -copy a ponter s, alocates memory and returns the copy ptr*/
/* ************************************************************************** */
char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*copy_s;

	s_len = ft_strlen(s);
	copy_s = malloc(s_len + 1);
	if (!copy_s)
		return (NULL);
	ft_memcpy(copy_s, s, s_len + 1);
	return (copy_s);
}
