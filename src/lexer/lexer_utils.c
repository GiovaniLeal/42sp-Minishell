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

/* Returns the parsing state based on the given character.

   - '\'' → inside single quotes
   - '"'  → inside double quotes
   - otherwise → general state
*/
int	state_status(char c)
{
	if (c == '\'')
		return (STATE_IN_SQUOTE);
	else if (c == '"')
		return (STATE_IN_DQUOTE);
	else
		return (STATE_GENERAL);
}

/* Checks if the character is a shell operator.

   Supported operators:
   - '>'  (output redirection)
   - '<'  (input redirection)
   - '|'  (pipe)
*/
int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

/* Checks if the character is a whitespace (space or tab) */
int	is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}

/* Skips leading whitespace characters (spaces and tabs)
   and returns a pointer to the first non-whitespace character */
char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}
