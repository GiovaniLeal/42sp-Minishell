/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:45:41 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/15 14:40:15 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*get_key = */
char	*get_key(char *str, int *index)
{
	char	*key;

	key = ft_strdup("");
	while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
	{
		key = append_char(key, str[*index]);
		(*index)++;
	}
	return (key);
}

static char	*last_return(t_shell *shell, char *new, char *res)
{
	char	*exit_str;

	exit_str = ft_itoa(shell->last_exit);
	new = ft_strjoin(res, exit_str);
	free(exit_str);
	free(res);
	return (new);
}

/*handle_dollar*/
char	*handle_dollar(char *res, char *str, int *index, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*new;

	(*index)++; // pula o '$'
	if (str[*index] == '?')
	{
		(*index)++;
		return (last_return(shell, new, res));
	}
	key = get_key(str, index);
	if (key[0] == '\0')
	{
		free(key);
		return (append_char(res, '$'));
	}
	value = get_environment(shell->lst_env, key);
	free(key);
	if (!value)
		return (res);
	new = ft_strjoin(res, value);
	free(res);
	return (new);
}

/*Concatena caractere a uma string*/
char	*append_char(char *res, char add)
{
	char	tmp[2];
	char	*final_str;

	tmp[0] = add;
	tmp[1] = '\0';
	final_str = ft_strjoin(res, tmp);
	free(res);
	return (final_str);
}

/* Para checar se o caractere é aspas duplas ou simples*/
int	check_quote(char c)
{
	if (c == '\'')
		return (STATE_IN_SQUOTE);
	if (c == '\"')
		return (STATE_IN_DQUOTE);
	return (STATE_GENERAL);
}
