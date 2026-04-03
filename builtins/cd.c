/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:02:46 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/02 20:02:46 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_node(char *key, t_env *lst_env)
{
	t_env	*temp_node;

	temp_node = lst_env;
	while (temp_node && ft_strcmp(temp_node->key, key) != 0)
		temp_node = temp_node->next;
	return (temp_node);
}

static void update_env(char *key, char *path, t_env **lst_env)
{
	t_env	*aux_node;
	char	*new_node_str;

	aux_node = find_node(key, *lst_env);
	if (aux_node)
	{
		free(aux_node->value);
		aux_node->value = ft_strdup(path);
	}
	else 
	{
		new_node_str = str_join_three(key, '=', path);
		aux_node = create_environment(new_node_str);
		add_environment(lst_env, aux_node);
		free(new_node_str);
	}

}

int	exec_cd(char **argv, t_env *env)
{
	int	status;
	char	*current_pwd;
	char	*new_pwd;

	if ((argv[1] && argv[2]) || !argv[1])
	{
		ft_printf("cd : too many arguments\n");
		return (1);
	}
	current_pwd = getcwd(NULL, 0);
	status = chdir(argv[1]);
	if (status)
	{
		perror("cd");
		free(current_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("pwd");
		free(current_pwd);
		return (1);
	}
	update_env("OLDPWD", current_pwd, &env);
	update_env("PWD", new_pwd, &env);
	free(current_pwd);
	free(new_pwd);
	return (0);
}
