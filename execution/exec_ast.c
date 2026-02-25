/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:00:29 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/25 15:05:18 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exec_node(t_ast *node, char **envp)
{
	if (!node || !node->argv || !node->argv[0])
		return (0);
	return (exec_simple(node, envp));
}

int	exec_ast_tree(t_ast *tree, char **envp)
{
	if (!tree)
		return (0);
	if (tree->type == NODE_CMD)
		return (exec_node(tree, envp));
	return (0);
}