/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:36:49 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/13 16:36:49 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* !! - APAGAR ESSE ARQUIVO ANTES DO ENVIO - ARQUIVO DE TESTE DO LEXER!! - */

/*  Funcao auxiliar para tester de vizualização de lista de tokens criadas       */
char	*token_type_to_str(t_token_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	if (type == T_PIPE)
		return ("T_PIPE");
	if (type == T_REDIR_IN)
		return ("T_REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	if (type == T_APPEND)
		return ("T_APPEND");
	if (type == T_HEREDOC)
		return ("T_HEREDOC");
	return ("UNKNOWN");
}

/*             Tester para vizualizar lista de tokens criadas                */
void	print_tokens(t_token  *tokens_list)
{
	int	count_node;

	count_node = 0;
	while(tokens_list != NULL)
	{
		//ft_printf(" %d", count_node);
		ft_printf(" - VALUE : %s\n", tokens_list->value);
		ft_printf(" - TYPE : %s\n", token_type_to_str(tokens_list->type));
		tokens_list = tokens_list->next;
		count_node++;
	}
}