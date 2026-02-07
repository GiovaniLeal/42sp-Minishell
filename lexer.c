/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:16:11 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/06 20:16:11 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Incluir nessa etapa : 
	Funcao -> add_back_token_lst
	1 - Teste simples : ls -l | grep txt
	2 - Incluir suporte a aspas
	3 - Validar erros de sintaxe (||| , | |, l1s )
*/
/*    Atribui a o o type do nó correspondente e retorna o tamanho da str a 
ser armazenada em value   */
int	get_token_type_and_len(t_token_type *node_type, char *str)
{
	int	len;

	len = 0;
	if (str[0] == '>' && str[1] == '>')
		return (*node_type = T_APPEND, 2);
	if (str[0] == '<' && str[1] == '<')
		return (*node_type = T_HEREDOC, 2);
	if (str[0] == '<')
		return (*node_type = T_REDIR_IN, 1);
	if (str[0] == '>')
		return (*node_type = T_REDIR_OUT, 1);
	if (str[0] == '|')
		return (*node_type = T_PIPE, 1);
	else
	{
		*node_type = T_WORD;
		while (str[len] && str[len] != ' ' && str[len] != '\t'
			&& str[len] != '|' && str[len] != '<'
			&& str[len] != '>')
			len++;
		return (len);
	}
}

/* Cria e retorna lista com tokens(comandos) digitados pelo usuário */
t_token	*lexer(char *str)
{
	int		value_len;
	t_token	*new_token;
	t_token	*lst_tokens;

	lst_tokens = NULL;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!*str)
			break ;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->next = NULL;
		value_len = get_token_type_and_len(&new_node->type, str);
		new_node->value = ft_substr(str, 0, value_len);
		add_back_token_lst(&lst, new_token);
		str += value_len;
	}
	return (lst_tokens);
}
