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


/* Atribui tipo T_WORD E retorna o tamanho da str. Verifica o status de aspas 
simples e duplas e caso nao seja fechado corretamente retorna -1*/
static int read_word(t_token_type *type, char *str)
{
    int len = 0;
    t_state state = STATE_GENERAL;
    t_state next;

    *type = T_WORD;
    while (str[len])
    {
        if (state == STATE_GENERAL &&
            (is_operator(str[len]) || is_white_space(str[len])))
            break;

        next = state_status(str[len]);

        if (state == STATE_GENERAL && next != STATE_GENERAL)
            state = next;
        else if (state != STATE_GENERAL && next == state)
            state = STATE_GENERAL;

        len++;
    }

    if (state != STATE_GENERAL)
        return (-1);
    return (len);
}



/*    Atribui a o o type do nó correspondente e retorna o tamanho da str a 
ser armazenada em value   */
static int	get_token_type_and_len(t_token_type *node_type, char *str)
{
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
		return (read_word(node_type, str));
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
		value_len = get_token_type_and_len(&new_token->type, str);
		if (value_len <= 0)
		{
			free(new_token);
			return (NULL);
		}
		new_token->value = ft_substr(str, 0, value_len);
		if (!new_token->value)
		{
			free(new_token);
			return (NULL);
		}
		add_back_token_lst(&lst_tokens, new_token);
		str += value_len;
	}
	return (lst_tokens);
}

