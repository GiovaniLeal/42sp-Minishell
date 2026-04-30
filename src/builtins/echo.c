/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:13:54 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/28 16:38:15 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*          		Function Prototypes 		        */
/* ************************************************************************** */
int			exec_echo(char **str_array);
static int	is_n_option(char *str);

/* ************************************************************************** */
/* 	 Executes the 'echo' built-in command:                          */
/*  1. Option Parsing: Checks for one or more "-n" flags to suppress the      */
/*  trailing newline.                                                         */
/*  2. Argument Printing: Iterates through the remaining strings, printing    */
/*  each one followed by a space if another argument follows.                 */
/*  3. Final Output: Appends a newline character unless the "-n" option       */
/*  was active.Returns 0 on completion.                                       */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                      Validates the echo "-n" option:                       */
/* 1. Checks if the string starts with a hyphen and is not empty.             */
/* 2. Ensures that all subsequent characters are strictly the letter 'n'.     */
/* 3. Returns 1 if the string matches the pattern -n[n...], and 0 if it       */
/* contains any other character or is just a single hyphen.                   */
/* This ensures compliance with Bash's behavior for the echo command.         */
/* ************************************************************************** */
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
