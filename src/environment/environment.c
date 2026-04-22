/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:06:11 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/08 21:06:11 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*adiciona na ordem de leitura o novo nó na lista de enviroment*/
void	add_environment(t_env **lst, t_env *node)
{
	t_env	*temp;

	if (!node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

/* Cria um novo ambiente(nó) e faz o parsing da str recebida */
t_env	*create_environment(char *str)
{
	int		index;
	t_env	*new_node;

	index = 0;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	while (str[index] && str[index] != '=')
		index++;
	new_node->key = ft_substr(str, 0, index);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (str[index] == '=')
		index++;
	new_node->value = ft_strdup(str + index);
	if (!new_node->value)
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}


/* Percorre o array de envp e chama as funçoes responsáveis pela criação da 
lista de enviromets*/
t_env	*add_env(char **envp)
{
	int		i;
	t_env	*list_environments;
	t_env	*new_env;

	i = 0;
	list_environments = NULL;
	while (envp[i])
	{
		new_env = create_environment(envp[i]);
		if (!new_env)
		{
			free_env_list(list_environments);
			return (NULL);
		}
		add_environment(&list_environments, new_env);
		i++;
	}
	return (list_environments);
}
