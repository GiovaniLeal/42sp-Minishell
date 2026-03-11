/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:26:22 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/05 18:26:22 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Funcao de testes que será otimizada no futuro*/
static t_ast	*process_input(char *input)
{
	t_token	*tokens;
	t_ast	*parser_tree;

	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	parser_tree = parser(tokens);
	if (!parser_tree)
	{
		ft_printf("Syntax error\n");
		free_token_list(tokens);
		return (NULL);
	}
	printf("========= LEXER LIST ==========\n");
	print_tokens(tokens);
	printf("========= PARSER ============\n");
	print_ast_tree(parser_tree, 0);
	free_token_list(tokens);
	return (parser_tree);
}

/*Nova funcao de orquestradora de processos*/
void	start_shell(t_shell *shell)
{
	(void)shell;
	char	*input;
	t_ast	*tree;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tree = process_input(input);
		 if (tree)
		{
		 	//expand_ast(tree, shell);
			//print_ast_tree(parser_tree, 0);
			free(input);
			return ;
		// 	exec_ast_tree(tree, shell); // atualizar
		 	free_ast(tree);
		}
		free(input);
	}
}

/* ************************************************************************** */
/* 				MAIN                                  */
/* ************************************************************************** */
int	main(int argc, char **argv, char **envp)
{
	
	t_shell	shell;

	(void)argc;
	(void)argv;
	using_history();
	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		tree = process_input(input);
		if (tree)
		{
			exec_ast_tree(tree, envp);
			free_ast(tree);
		}
	}
	free(input);
	rl_clear_history();
	return (0);
}
