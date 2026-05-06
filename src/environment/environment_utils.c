/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:56 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/08 22:23:56 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_join_three(char *key, char c, char *value)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	if (!key || !value)
		return (NULL);
	len = ft_strlen(key) + ft_strlen(value) + 2;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (key[i])
		str[j++] = key[i++];
	str[j++] = c;
	i = 0;
	while (value[i])
		str[j++] = value[i++];
	str[j] = '\0';
	return (str);
}

void	free_env_array(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	env_size(t_env *lst_env)
{
	int	count;

	count = 0;
	while (lst_env)
	{
		lst_env = lst_env->next;
		count++;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**array;

	i = 0;
	size = env_size(env);
	array = malloc (sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	while (env)
	{
		array[i] = str_join_three(env->key, '=', env->value);
		if (!array[i])
		{
			free_env_array(array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	*get_environment(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
