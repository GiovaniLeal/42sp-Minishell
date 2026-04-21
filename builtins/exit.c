/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:54:06 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/21 18:52:23 by anunes-o         ###   ########.fr       */
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

static int	no_exit_status(t_shell *shell)
{
	ft_putstr_fd("exit\n", 2);
	shell->exit_flag = 1;
	return (shell->last_exit);
}

static int	no_numeric_status(t_shell *shell, char **argv)
{
	ft_putstr_fd("exit\n", 2);
	shell->exit_flag = 1;
	shell->last_exit = 0;
	return (error_msg(argv[0], argv[1], "numeric argument required", 2));
}

int	ft_exit(char **argv, t_shell *shell)
{
	long	nbr;
	int		error;

	if ((!argv[1]))
		return (no_exit_status(shell));
	if (!is_numeric(argv[1]))
		return (no_numeric_status(shell, argv));
	if (argv[2])
		return (error_msg(argv[0], NULL, "too many arguments", 1));
	nbr = ft_atol_safe(argv[1], &error);
	if (error)
	{
		ft_putstr_fd("exit\n", 2);
		shell->exit_flag = 1;
		shell->last_exit = 2;
		return (error_msg(argv[0], argv[1], 
				"numeric argument required", 2));		
	}
	ft_putstr_fd("exit\n", 2);
	shell->exit_flag = 1;
	shell->last_exit = (unsigned char)nbr;
	return ((unsigned char)nbr);
}
