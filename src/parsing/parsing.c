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

/* Adds a redirection (>, <, >>, <<) to the command's redirection list.

   - Allocates a new redirection node
   - Duplicates the file name
   - Appends the node to the end of the redirection list

   Returns 1 on success, 0 on allocation failure
*/
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

/* Adds an argument to the command node.

   - If argv is NULL → initializes it with the first argument
   - Otherwise → delegates to add_new_arg to append a new argument

   Returns 1 on success, 0 on allocation failure
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

/* Parses a simple command from consecutive tokens (WORD and REDIR).

   - Builds a command node (argv + redirections)
   - Handles argument insertion and redirection parsing
   - Validates syntax (e.g., redirection must be followed by a WORD)

   Returns:
   - A valid command node on success
   - NULL on syntax error or allocation failure
*/
t_ast	*parse_command(t_token **current_token)
{
	t_ast	*command;

	command = new_cmd_node();
	if (!command)
		return (NULL);
	while (*current_token && ((*current_token)->type == T_WORD
			|| is_redir((*current_token)->type)))
	{
		if (!handle_token(command, current_token))
			return (free_ast(command), NULL);
	}
	if (!command->argv)
		return (free_ast(command), NULL);
	return (command);
}

/* Builds a pipeline AST by chaining commands with the '|' operator.

   - Parses the left command
   - For each pipe token, parses the right command
   - Creates a pipe node linking left and right subtrees

   Returns:
   - The root of the pipeline AST
   - NULL on syntax error or allocation failure
*/
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

/* Main parser entry point: converts a token list into an AST.

   - Starts parsing from the pipeline level
   - Ensures all tokens are consumed (no leftover tokens)

   Returns:
   - A valid AST on success
   - NULL if a syntax error occurs or parsing is incomplete
*/
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
