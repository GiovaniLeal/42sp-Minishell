/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:48:09 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/21 19:48:09 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Adiciona um redirecionamento (>, <, >>, <<) à lista do comandos */
int	add_redir(t_ast *cmd, t_token_type type, char *file)
{
	t_redir	*new;
	t_redir	*temp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->file = ft_strdup(file);
	if (!new->file)
	{
		free(new);
		return (0);
	}
	new->type = type;
	new->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		temp = cmd->redirs;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (1);
}

/*
** Inicializa argv se for o primeiro argumento
** ou adiciona um novo argumento se argv já existir.
*/
int	add_arg(t_ast *cmd_node, char *token_value)
{
	if (!cmd_node->argv)
	{
		cmd_node->argv = malloc(sizeof(char *) * 2);
		if (!cmd_node->argv)
			return (0);
		cmd_node->argv[0] = ft_strdup(token_value);
		if (!cmd_node->argv[0])
		{
			free(cmd_node->argv);
			cmd_node->argv = NULL;
			return (0);
		}
		cmd_node->argv[1] = NULL;
		return (1);
	}
	return (add_new_arg(cmd_node, token_value));
}

/* Cria um nó de comando a partir dos tokens WORD e REDIR consecutivos */
/* Retorna NULL em caso de erro de sintaxe ou comando inválido */
t_ast	*parse_command(t_token **current_token)
{
	t_ast	*command;

	command = new_cmd_node();
	if (!command)
		return (NULL);
	while (*current_token && (*current_token)->type == T_WORD)
	{
		if (!add_arg(command, (*current_token)->value))
			return (free_ast(command), NULL);
		*current_token = (*current_token)->next;
	}
	while (*current_token && is_redir((*current_token)->type))
	{
		if (!(*current_token)->next
			|| (*current_token)->next->type != T_WORD)
			return (free_ast(command), NULL);
		if (!add_redir(command,
				(*current_token)->type,
				(*current_token)->next->value))
			return (free_ast(command), NULL);
		*current_token = (*current_token)->next->next;
	}
	if (!command->argv)
		return (free_ast(command), NULL);
	return (command);
}

/* Constrói a árvore de pipes encadeando comandos com o operador '|' */
/* Retorna a raiz da AST do pipeline ou NULL em caso de erro */
t_ast	*parse_pipeline(t_token **current_token)
{
	t_ast	*left_cmd;
	t_ast	*right_cmd;
	t_ast	*pipe_node;

	left_cmd = parse_command(current_token);
	if (!left_cmd)
		return (NULL);
	while (*current_token && (*current_token)->type == T_PIPE)
	{
		*current_token = (*current_token)->next;
		if (!*current_token)
			return (free_ast(left_cmd), NULL);
		right_cmd = parse_command(current_token);
		if (!right_cmd)
			return (free_ast(left_cmd), NULL);
		pipe_node = new_pipe_node(left_cmd, right_cmd);
		if (!pipe_node)
			return (free_ast(left_cmd), free_ast(right_cmd), NULL);
		left_cmd = pipe_node;
	}
	return (left_cmd);
}

/* Função principal do parser: converte a lista de tokens em uma AST */
/* Retorna NULL se houver erro de sintaxe ou tokens restantes */
t_ast	*parser(t_token *token_list)
{
	t_ast	*parse_tree;
	t_token	*current;

	current = token_list;
	parse_tree = parse_pipeline(&current);
	if (!parse_tree)
		return (NULL);
	if (current)
	{
		free_ast(parse_tree);
		return (NULL);
	}
	return (parse_tree);
}
