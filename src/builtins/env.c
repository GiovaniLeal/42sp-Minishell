/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:15:45 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/05 16:15:45 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                  Executes the 'env' built-in command:                      */
/* 1. Argument Validation: Returns an error if any arguments are provided.    */
/* 2. Environment Iteration: Traverses the linked list and skips entries      */
/* without an assigned value.                                                 */
/* 3. String Formatting: Reconstructs the "KEY=VALUE" pair for each entry.    */
/* 4. Memory Management: Frees the formatted string immediately after         */
/* printing to prevent accumulation of leaks during iteration.                */
/* Returns 0 on success, or 1 on error.                                       */
/* ************************************************************************** */
int	exec_env(char **argv, t_env *env)
{
	char	*key_plus_path;

	if (argv[1])
	{
		ft_printf("env: too many arguments\n");
		return (1);
	}
	while (env)
	{
		if (ft_strcmp(env->value, "") != 0)
		{
			key_plus_path = str_join_three(env->key, '=', env->value);
			if (key_plus_path)
			{
				ft_printf("%s\n", key_plus_path);
				free(key_plus_path);
			}
		}
		env = env->next;
	}
	return (0);
}
