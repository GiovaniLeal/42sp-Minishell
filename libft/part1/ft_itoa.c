/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:39:18 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/24 16:39:18 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*  2 - Count digits, add 1 if number is negative                             */
/* ************************************************************************** */
static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

/* ************************************************************************** */
/* 1 - ft_itoa: Converts an integer to a string                               */
/* ************************************************************************** */
char	*ft_itoa(int n)
{
	int			str_len;
	char		*string;
	long		number;

	number = n;
	str_len = ft_count_digits(number);
	string = malloc(sizeof(char) * (str_len + 1));
	if (!string)
		return (NULL);
	string[str_len] = '\0';
	if (number == 0)
		string[0] = '0';
	if (number < 0)
	{
		string[0] = '-';
		number = -number;
	}
	while (number)
	{
		string[--str_len] = (number % 10) + '0';
		number = number / 10;
	}
	return (string);
}
