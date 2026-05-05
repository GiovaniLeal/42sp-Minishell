/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:26:22 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/27 18:26:22 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*          		Function Prototypes 		        */
/* ************************************************************************** */
int				main(int argc, char **argv, char **envp);
void			start_shell(t_shell *shell);
static int		process_cycle(t_shell *shell, char *input);
static t_ast	*process_input(char *input);

/* ************************************************************************** */
/* 	                       MAIN                                     */
/* ************************************************************************** */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	using_history();
	setup_signals();
	shell.lst_env = add_env(envp);
	shell.exit_flag = 0;
	shell.last_exit = 0;
	start_shell(&shell);
	free_env_list(shell.lst_env);
	rl_clear_history();
	return (shell.last_exit);
}

/* ************************************************************************** */
/*     Main program loop: displays the prompt and captures user input via     */
/*     readline, updates the last exit status if an interrupt signal was      */
/*     received, manages command history, and handles shell termination.      */
/* ************************************************************************** */
void	start_shell(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (get_signal())
		{
			shell->last_exit = get_signal();
			reset_signal();
		}
		if (!input)
			break ;
		if (*input)
			add_history(input);
		process_cycle(shell, input);
		free(input);
		if (shell->exit_flag)
			break ;
	}
}

/* ************************************************************************** */
/*                Manages the command processing cycle                        */
/*          1. Parses input into an Abstract Syntax Tree (AST).               */
/*          2. Processes heredoc redirections.                                */
/*          3. Performs environment variable expansion.                       */
/*          4. Executes the command tree.                                     */
/*          5. Frees the allocated AST memory to prevent leaks.               */
/* ************************************************************************** */
static int	process_cycle(t_shell *shell, char *input)
{
	t_ast	*tree;

	tree = process_input(input);
	if (!tree)
		return (0);
	shell->root = tree;
	if (apply_heredocs(tree) < 0)
	{
		free_ast(tree);
		return (0);
	}
	expand_ast(tree, shell);
	exec_ast_tree(tree, shell);
	free_ast(tree);
	return (0);
}

/* ************************************************************************** */
/*                Performs lexical and syntactic analysis:                    */
/* 1. Lexer: Tokenizes the input string into a list of symbols.               */
/* 2. Parser: Converts the token list into an Abstract Syntax Tree (AST).     */
/* 3. Error Handling: Displays "Syntax error" and cleans up if parsing fails. */
/* 4. Cleanup: Frees the temporary token list before returning the tree.      */
/* ************************************************************************** */
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
		ft_putstr_fd("Syntax error\n", 2);
		free_token_list(tokens);
		return (NULL);
	}
	free_token_list(tokens);
	return (parser_tree);
}
