/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:36:08 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/28 18:00:37 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*          		Function Prototypes 		        */
/* ************************************************************************** */
int			exec_unset(char **argv, t_shell *shell);
static void	remove_env_node(t_env **lst, char *key);

/* ************************************************************************** */
/* executes the unset built-in                                                */
/* 1. iterates through each argument provided by the user                     */
/* 2. for each key, calls remove_env_node to search and delete from list      */
/* 3. returns 0 upon completion                                               */
/* ************************************************************************** */
int	exec_unset(char **argv, t_shell *shell)
{
	int	i;

	if (!argv || !argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		remove_env_node(&shell->lst_env, argv[i]);
		i++;
	}
	return (0);
}

static void	remove_env_node(t_env **lst, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*lst = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
