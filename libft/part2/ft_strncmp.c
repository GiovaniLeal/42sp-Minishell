/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:51:31 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/28 14:51:31 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
// STRING_COMPARE - Compare up to `n` characters of two strings
/* ************************************************************************** */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cha_s1;
	unsigned char	*cha_s2;

	i = 0;
	cha_s1 = (unsigned char *)s1;
	cha_s2 = (unsigned char *)s2;
	while (i < n && (cha_s1[i] == cha_s2[i]) && (cha_s1[i] || cha_s2[i]))
		i++;
	if (i == n)
		return (0);
	return (cha_s1[i] - cha_s2[i]);
}
