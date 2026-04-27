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

/* Percorre a str de token e retorna uma nova string com a expansão correta*/
char *expand_tokens(char *str, t_shell *shell)
{
	int		i;
	int		state;
	char	*result;

	i = 0;
	state = STATE_GENERAL;
	result = ft_strdup("");

	while (str[i])
	{
		// SINGLE QUOTE
		if (str[i] == '\'' && state != STATE_IN_DQUOTE)
		{
			state = (state == STATE_IN_SQUOTE) ? STATE_GENERAL : STATE_IN_SQUOTE;
			i++; // remove a aspa estrutural
			continue;
		}

		// DOUBLE QUOTE
		if (str[i] == '"' && state != STATE_IN_SQUOTE)
		{
			state = (state == STATE_IN_DQUOTE) ? STATE_GENERAL : STATE_IN_DQUOTE;
			i++; // remove a aspa estrutural
			continue;
		}

		// EXPANSÃO
		if (str[i] == '$' && state != STATE_IN_SQUOTE)
		{
			result = handle_dollar(result, str, &i, shell);
			continue;
		}

		// CARACTERE NORMAL (inclui aspas "inofensivas")
		result = append_char(result, str[i]);
		i++;
	}
	return (result);
}

void	expand_redirs(t_redir	*redirs, t_shell *shell)
{
	char	*new_file;

	while (redirs)
	{
		new_file = expand_tokens(redirs->file, shell);
		free(redirs->file);
		redirs->file = new_file;
		redirs = redirs->next;
	}
}

/*Percorre o array, chama funcao que expande o token da string e realoca 
a string do array*/
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

//Percorre a arvore e chama funcao de expansão 
// caso o nó seja de comando
void	expand_ast(t_ast *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		expand_command(node->argv, shell);
		expand_redirs(node->redirs, shell);
	}
	expand_ast(node->left, shell);
	expand_ast(node->right, shell);
}
