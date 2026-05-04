/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:28:40 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/21 19:28:40 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                             STANDART LIBRARIES                             */
/* ************************************************************************** */
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************************************************** */
/*                          DEFINED HEADERS                                   */
/* ************************************************************************** */
# include "libft.h"
# include "ft_printf.h"
# include "environment.h"
# include "tokens.h"
# include "parsing.h"
# include "execution.h"
# include "environment.h"
# include "expander.h"
# include "signals.h"
# include "builtins.h"

/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

// ------------------------------------------------- utils.c
void	free_split(char **array);
int		error_msg(char *cmd, char *detail, char *msg, int error_nbr);
long	ft_atol_safe(const char *nptr, int *error);
#endif
