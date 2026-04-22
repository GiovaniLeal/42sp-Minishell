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
		if (env->value)
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
