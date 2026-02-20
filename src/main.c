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

/* ************************************************************************** */
/* 		          	MAIN                                  */
/* ************************************************************************** */
int	main(void)
{
	char	*input;
	t_token	*tokens;

	using_history();
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		if (!input)
			break;
		tokens = lexer(input);
		if (!tokens)
		{
			free(input);
			continue;
		}
		print_tokens(tokens);
		free_token_list(tokens);
		free(input);
	}
	rl_clear_history();
	return (0); 
}