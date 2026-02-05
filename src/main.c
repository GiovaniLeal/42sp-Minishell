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

t_token	lexer(char *str)
{
	
}

int	main(int arc, char **argv)
{
	int	str;

	str = 0;
	t_token	*token_node;
	t_token	*token_lst;
	while (argv[str])
	{
		token_node = lexer(argv[str]);
		ft_lstadd_back_bonus(token_lst, token_node);
		str++;
	}
	return (0); //isso ainda irá mudar, vamos deixar assim por hora.
}