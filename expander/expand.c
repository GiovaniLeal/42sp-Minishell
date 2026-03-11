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
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			result = handle_dollar(result, str, &i, shell);
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}

/*Percorre o array, chama funcao que expande o token da string e realoca 
a string do array*/
void	expand_command(char **array, t_shell *shell)
{
	int	i;
	char	*new_string;

	i = 0;
	while (array[i])
	{
		new_string = expand_tokens(array[i], shell);
		free(array[i]);
		array[i] = new_string;
		i++;
	}
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
		//expand_redirs(node->redirs, shell);
	}
	expand_ast(node->left, shell);
	expand_ast(node->right, shell);
}
