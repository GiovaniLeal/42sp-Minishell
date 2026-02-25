/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:28:57 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/24 22:28:57 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "minishell.h"

/* imprime espaços para indentação */
static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
}

/* imprime lista de redirecionamentos */
static void	print_redirs(t_redir *redir, int depth)
{
	while (redir)
	{
		print_indent(depth);
		printf("REDIR: type=%d file=%s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

/* imprime argv */
static void	print_argv(char **argv, int depth)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		print_indent(depth);
		printf("ARGV[%d]: %s\n", i, argv[i]);
		i++;
	}
}

/* travessia em pré-ordem com indentação */
void	print_ast_tree(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_PIPE)
		printf("NODE_PIPE\n");
	else if (node->type == NODE_CMD)
		printf("NODE_CMD\n");
	if (node->type == NODE_CMD)
	{
		print_argv(node->argv, depth + 1);
		print_redirs(node->redirs, depth + 1);
	}
	print_ast_tree(node->left, depth + 1);
	print_ast_tree(node->right, depth + 1);
}
