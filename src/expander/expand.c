/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:38:06 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/07 19:38:06 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tokens(char *str, t_shell *shell)
{
	int		i;
	int		state;
	char	*result;

	i = 0;
	state = STATE_GENERAL;
	result = ft_strdup("");
	while (str[i])
	{
		if (update_state_quote(&state, str, &i))
			continue ;
		if (str[i] == '$' && state != STATE_IN_SQUOTE)
		{
			result = handle_dollar(result, str, &i, shell);
			continue ;
		}
		result = append_char(result, str[i]);
		i++;
	}
	return (result);
}

void	expand_command(char **array, t_shell *shell)
{
	int		i;
	int		j;
	char	*new_string;

	i = 0;
	while (array[i])
	{
		new_string = expand_tokens(array[i], shell);
		free(array[i]);
		array[i] = new_string;
		i++;
	}
	i = 0;
	j = 0;
	while (array[i])
	{
		if (array[i][0] != '\0')
			array[j++] = array[i];
		else
			free(array[i]);
		i++;
	}
	array[j] = NULL;
}

void	expand_ast(t_ast *node, t_shell *shell)
{
	char	*new_file;
	t_redir	*tmp;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		expand_command(node->argv, shell);
		tmp = node->redirs;
		while (tmp)
		{
			new_file = expand_tokens(tmp->file, shell);
			free(tmp->file);
			tmp->file = new_file;
			tmp = tmp->next;
		}
	}
	expand_ast(node->left, shell);
	expand_ast(node->right, shell);
}

int	update_state_quote(int *state, char *str, int *i)
{
	if (str[*i] == '\'' && (*state) != STATE_IN_DQUOTE)
	{
		if ((*state) == STATE_IN_SQUOTE)
			(*state) = STATE_GENERAL;
		else
			(*state) = STATE_IN_SQUOTE;
		(*i)++;
		return (1);
	}
	else if (str[*i] == '"' && (*state) != STATE_IN_SQUOTE)
	{
		if ((*state) == STATE_IN_DQUOTE)
			(*state) = STATE_GENERAL;
		else
			(*state) = STATE_IN_DQUOTE;
		(*i)++;
		return (1);
	}
	return (0);
}

int	change_quote_status(int state, char c)
{
	if (c == '\'' && state != STATE_IN_DQUOTE)
	{
		if (state == STATE_IN_SQUOTE)
			return (STATE_GENERAL);
		else
			return (STATE_IN_SQUOTE);
	}
	if (c == '\"' && state != STATE_IN_SQUOTE)
	{
		if (state == STATE_IN_DQUOTE)
			return (STATE_GENERAL);
		else
			return (STATE_IN_DQUOTE);
	}
	return (state);
}
