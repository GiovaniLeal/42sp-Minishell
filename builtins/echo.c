/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:13:54 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/02 19:23:45 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Percorre a string e conta o numero de argumentos 'n'
/* Retorna 1 se todos os caracteres depois de '-'são 'n'e 0 em caso contrário*/
static int	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	exec_echo(char **str_array)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (str_array[i] && is_n_option(str_array[i]))
	{
		newline = 0;
		i++;
	}
	while (str_array[i])
	{
		ft_printf("%s", str_array[i]);
		if (str_array[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
