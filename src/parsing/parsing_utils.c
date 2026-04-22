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
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}

/* Criar nó de PIPE usando a struct t_ast (arvore sintática)	     */
t_ast	*new_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}

/* 
** Cria um novo vetor argv maior, copia os argumentos existentes,
** adiciona o novo valor no final e atualiza cmd_node->argv.
*/
int	add_new_arg(t_ast *cmd_node, char *value)
{
	int		i;
	char	**new_arg;

	i = 0;
	while (cmd_node->argv[i])
		i++;
	new_arg = malloc(sizeof(char *) * (i + 2));
	if (!new_arg)
		return (0);
	i = 0;
	while (cmd_node->argv[i])
	{
		new_arg[i] = cmd_node->argv[i];
		i++;
	}
	new_arg[i] = ft_strdup(value);
	if (!new_arg[i])
	{
		free(new_arg);
		return (0);
	}
	new_arg[i + 1] = NULL;
	free(cmd_node->argv);
	cmd_node->argv = new_arg;
	return (1);
}
