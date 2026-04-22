/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:36:08 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/17 16:08:57 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(char **argv, t_shell *shell)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 1;
	while (argv[i])
	{
		prev = NULL;
		current = shell->lst_env;
		while (current)
		{
			if (ft_strcmp(current->key, argv[i]) == 0)
			{
				if (prev == NULL)
					shell->lst_env = current->next;
				else
					prev->next = current->next;
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
