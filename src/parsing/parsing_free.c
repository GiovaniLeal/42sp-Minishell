/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:07:05 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/24 23:07:05 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;

	// 🔴 sempre desce na árvore
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);

	// 🔴 sempre libera argv se existir
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
			free(node->argv[i++]);
		free(node->argv);
	}

	// 🔴 sempre libera redirections se existir
	if (node->redirs)
		free_redirs(node->redirs);

	free(node);
}
