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

static int	read_word(t_token_type *type, char *str)
{
	int		len;
	t_state	state;
	t_state	next;

	len = 0;
	state = STATE_GENERAL;
	*type = T_WORD;
	while (str[len])
	{
		if (state == STATE_GENERAL
			&& (is_operator(str[len])
				|| is_white_space(str[len])))
			break ;
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

static t_token	*create_token(char *str, int *len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	*len = get_token_type_and_len(&token->type, str);
	if (*len <= 0)
	{
		free(token);
		return (NULL);
	}
	token->value = ft_substr(str, 0, *len);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_token	*lexer(char *str)
{
	t_token	*lst_tokens;
	t_token	*new_token;
	int		len;

	lst_tokens = NULL;
	while (*str)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
		new_token = create_token(str, &len);
		if (!new_token)
			return (NULL);
		add_back_token_lst(&lst_tokens, new_token);
		str += len;
	}
	return (lst_tokens);
}
