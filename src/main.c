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

/* Roteiro : 
	- Iniciar variavel global que armazena token lst && parser lst
	- Criar funcao de limpeza geral
	- Parser inicial 
*/


/* ************************************************************************** */
/* 		          	MAIN                                  */
/* ************************************************************************** */
int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_ast	*parser_tree;

	using_history();
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		if (*input)
			add_history(input);
		tokens = lexer(input);
		if (!tokens)
		{
			free(input);
			continue;
		}
		parser_tree = parser(tokens);
		//execute();
		printf("========= LEXER LIST ==========");
		print_tokens(tokens);
		printf("========= PARSER ============");

		free_token_list(tokens);
		free(input);
	}
	rl_clear_history();
	return (0); 
}
