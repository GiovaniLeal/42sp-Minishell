/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:54:06 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/06 16:24:09 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*          		Function Prototypes 		        */
/* ************************************************************************** */
int			ft_exit(char **argv, t_shell *shell);
static int	no_numeric_status(t_shell *shell, char **argv);
static int	no_exit_status(t_shell *shell);
static int	is_numeric(char	*str);

/* ************************************************************************** */
/*                 Executes the 'exit' built-in command:                      */
/*   1. No Arguments: Exits using the last command's exit status.             */
/*   2. Numeric Validation: Ensures the first argument is a valid number      */
/*    and fits within 'long' limits using a safe atol conversion.             */
/*  3. Argument Count: If multiple arguments are provided, it prevents        */
/*   termination and returns an error message ("too many arguments").         */
/*  4. Finalization: Sets the exit_flag and truncates the return status to    */
/*   an unsigned char (0-255) as per POSIX standards.                         */
/* ************************************************************************** */
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
		shell->exit_flag = 1;
		shell->last_exit = 2;
		return (error_msg(argv[0], argv[1],
				"numeric argument required", 2));
	}
	shell->exit_flag = 1;
	shell->last_exit = (unsigned char)nbr;
	return ((unsigned char)nbr);
}

/* ************************************************************************** */
/*          		Utils Functions		        */
/* ************************************************************************** */
static int	no_numeric_status(t_shell *shell, char **argv)
{
	shell->exit_flag = 1;
	shell->last_exit = 0;
	return (error_msg(argv[0], argv[1], "numeric argument required", 2));
}

static int	no_exit_status(t_shell *shell)
{
	shell->exit_flag = 1;
	return (shell->last_exit);
}

static int	is_numeric(char	*str)
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
