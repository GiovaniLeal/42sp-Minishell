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
static t_ast *process_input(char *input)
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
	char	*input;
	t_ast	*tree;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		if (*input)
			add_history(input);
		tree = process_input(input);
		if (tree)
		{
		 	expand_ast(tree, shell);
			print_ast_tree(tree, 0);
			exec_ast_tree(tree, shell);
			free(input);
		 	free_ast(tree);
			continue ;
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
	shell.lst_env = add_env(envp);
	shell.last_exit = 0;
	start_shell(&shell);
	free_env_list(shell.lst_env);
	rl_clear_history();
	return (0);
}
