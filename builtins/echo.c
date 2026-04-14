/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:13:54 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/14 15:56:49 by anunes-o         ###   ########.fr       */
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

static void	print_without_quotes(char *str)
{
	int		i;
	char	open_quote;

	open_quote = 0;
	i = 0;
	while (str[i])
	{
		if (!open_quote && (str[i] == '\'' || str[i] == '"'))
			open_quote = str[i];
		else if (open_quote && str[i] == open_quote)
			open_quote = 0;
		else
			ft_printf("%c", str[i]);
		i++;
	}
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
		print_without_quotes(str_array[i]);
		if (str_array[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
