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

/*ERROR_HANDLER*/
/*add_redir*/
/*ADD_ARG*/

/*Responsavel pela criacao de nós de comando e adicionar argumentos*/
/*Valida erro de sintaxe e se o comando possui redirecionamento (> / <<)*/
t_ast	*parse_command(t_token **current_token)
{
	t_ast	*command;

	command = new_cmd_node();
	while (*current_token && (*current)->type ==T_WORD)
	{
		add_arg(command_node, (*current_token)->value);
		*current_token = (*current_token)->next;
	}
	while (*current_token && is_redir((*current_token)->type))
	{
		if (!(*current_token)->next || (*current)->next->type != T_WORD)
			return (NULL); //ERRO DE SINTAXE
		add_redir();
		*current_token = (*current_token)->next->next;
	}
	if(!command->argv)
		return (NULL);
	return (command);
}

/*Funcao responsável pelo encadeamento de nós EX.:(esquerda, pipe, direita ) */
/*                 PIPE                   */
/*             /          \               */
/*     NO DE COMANDO      NO DE COMANDO   */
/*                                         */
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
			return (NULL);
		right_cmd = parse_command(current_token);
		if (!right_cmd)
			return (NULL);
		pipe_node = new_pipe_node(left, right);
	}
	return (pipe_node);
}

/* Funcao principal do parser - Pega a lista de tokens e retorna a arvore/ordem de execução*/
t_ast	*parser(t_token *token_list)
{
	t_ast	*parse_tree;
	t_token	*current;

	current = token_list;
	parse_tree = parse_pipeline(&current);
	if(!parse_tree || current)
		return (NULL);
	return (parse_tree);
}

