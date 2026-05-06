/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:45:41 by giodos-s          #+#    #+#             */
/*   Updated: 2026/05/06 15:56:58 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*last_return(t_shell *shell, char *res)
{
	char	*exit_str;
	char	*new;

	exit_str = ft_itoa(shell->last_exit);
	new = ft_strjoin(res, exit_str);
	free(exit_str);
	free(res);
	return (new);
}

char	*handle_dollar(char *res, char *str, int *index, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*new;

	(*index)++;
	if (str[*index] == '?')
	{
		(*index)++;
		return (last_return(shell, res));
	}
	if (!ft_isalnum(str[*index]) && str[*index] != '_')
	{
		res = append_char(res, '$');
		return (res);
	}
	key = get_key(str, index);
	value = get_environment(shell->lst_env, key);
	free(key);
	if (!value)
		return (res);
	new = ft_strjoin(res, value);
	free(res);
	return (new);
}

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

int	is_quote_to_remove(int prev_state, int new_state, char c)
{
	if ((c == '\'' || c == '\"') && prev_state != new_state)
		return (1);
	return (0);
}
