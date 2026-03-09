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

#include "minishell.c"

/*Funcao de expansão com redirecionamento*/
void	expand_redirections(t_redir *redir, t_env *env)
{
	while(redir)
	{
		redir->file = expand_string(redir->file, env);
		redir = redir->next;
	}
}

char *expand_variable(char *result, char *str, int *i, t_env *env)
{
	char var[256];
	char *value;
	int j;

	(*i)++;

	j = 0;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		var[j++] = str[(*i)++];

	var[j] = '\0';

	value = env_get(env, var);
	if (!value)
		value = "";

	return append_string(result, value);
}

/*Principal funcao de expansao (aqui apenas os casos $)*/
char	*expand_string(char *str, t_env *env)
{
	int	i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while(str[i])
	{
		if (str[i] == '$')
			result = expand_variable(result, str, &i, env);
		else
			result = append_char(char, str[i++]);
		//aqui o i++ nao deveria ficar fora do loop?
	}
	return (result)
}

/*Percorre todos os argumentos do nó e chama função responsável por 
expandir/modificar a string*/
void	*expand_command(t_ast *node, t_env *env)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		node->arg[i] = expand_string(node->argv[i], env);
		i++;
	}
	expand_redirections(node->redirs, env);
}

/* Identifica o tipo de nó e percorre a arvore sintática recursivamente */
void	expand_ast(t_ast *node, t_env *env)
{
	if (!node)
		return ;
	if (node->type ==NODE_CMD)
		expand_command(node, env);
	expand_ast(node->left, env);
	expand_ast(node->right, env);
}
