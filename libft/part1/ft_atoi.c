/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:58:39 by giodos-s          #+#    #+#             */
/*   Updated: 2025/11/02 15:04:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
//skip white spaces using  ascii 
/* ************************************************************************** */
static const char	*ft_skip_white_spaces(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	return (str);
}

/* ************************************************************************** */
//check sign - detect sign and move pointer
/* ************************************************************************** */
static const char	*ft_check_sign(const char *str, int *sign_out)
{
	*sign_out = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign_out = -1;
		str++;
	}
	return (str);
}

/* ************************************************************************** */
// Atoi = convert string to int
/* ************************************************************************** */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	str = ft_skip_white_spaces(str);
	str = ft_check_sign(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (sign * result);
}
