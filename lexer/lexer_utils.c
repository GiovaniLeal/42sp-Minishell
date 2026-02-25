/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:52:32 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/13 18:52:32 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retorna o enum correspondente*/
int	state_status(char c)
{
	if (c == '\'')
		return (STATE_IN_SQUOTE);
	else if (c == '"')
		return (STATE_IN_DQUOTE);
	else
		return (STATE_GENERAL);
}

/* Valida se o caractere é um operador unix */
int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

/* Verifica se o caractere é um espaço em branco*/
int	is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}
