/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:39:02 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/06 11:44:10 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clear_and_exit(t_shell *shell, int exit_status)
{
	if (shell->root)
		free_ast(shell->root);
	if (shell->lst_env)
		free_env_list(shell->lst_env);
	if (exit_status >= 0)
		exit(exit_status);
}
