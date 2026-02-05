/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:57:30 by giodos-s          #+#    #+#             */
/*   Updated: 2025/07/26 20:57:30 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* Converts an integer to its decimal representation and writes it to the fd  */
/* ************************************************************************** */

void	ft_putnbr_fd(int n, int fd)
{
	char	print_nb;
	long	numb;

	numb = n;
	if (numb < 0)
	{
		write(fd, "-", 1);
		numb *= -1;
	}
	if (numb > 9)
		ft_putnbr_fd(numb / 10, fd);
	print_nb = (numb % 10) + '0';
	write(fd, &print_nb, 1);
}
