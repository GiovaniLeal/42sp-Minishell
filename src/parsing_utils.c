/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:37:06 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/23 14:37:06 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Verifica se o token possui redirecionamentos 	                  */
int	is_redir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

/*	Adiciona nó de comando usando a struct t_ast(arvore sintática)     */
t_ast	*new_cmd_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type  = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}

/* Criar nó de PIPE usando a struct t_ast (arvore sintática)	     */
t_ast	*new_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (new_node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	node->argv = NULL;
	node->redirs = NULL;
	return (new_node);
}
