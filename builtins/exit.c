/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:54:06 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/19 16:29:06 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
/* após adicionar a variavel global, alterar essa função para retornar diferentes
 valores dependendo do status true ou false
*/
int	ft_exit(char **argv)
{
	long	nbr;
	int		error;

	if ((!argv[1]) || (is_numeric(argv[1]) && !argv[2]))
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (!is_numeric(argv[1]))
	{
		error_msg(argv[0], argv[1], "numeric argument required", 2);
		exit(2);
	}
	if (argv[2])
	{
		error_msg(argv[0], NULL, "too many arguments", 1);
		return (1);
	}
	nbr = ft_atol_safe(argv[1], &error);
	exit((unsigned char)nbr);
}
