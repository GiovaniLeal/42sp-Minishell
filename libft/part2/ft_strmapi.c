/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:31:26 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/24 18:31:26 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* Applies a function to each character of the input str to build a new strg .*/
/* ************************************************************************** */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*string;
	unsigned int	i;
	unsigned int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	string = malloc(s_len + 1);
	if (!string)
		return (NULL);
	string[s_len] = '\0';
	while (i < s_len)
	{
		string[i] = f(i, s[i]);
		i++;
	}
	return (string);
}
