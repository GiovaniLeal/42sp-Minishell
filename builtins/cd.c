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

static void	update_env(char *key, char *path, t_env **lst_env)
{
	t_env	*node;
	char	*new_node_str;
	char	*new_value;

	node = find_node(key, *lst_env);
	if (node)
	{
		new_value = ft_strdup(path);
		if (!new_value)
			return ;
		free(node->value);
		node->value = new_value;
	}
	else
	{
		new_node_str = str_join_three(key, '=', path);
		if (!new_node_str)
			return ;
		node = create_environment(new_node_str);
		add_environment(lst_env, node);
		free(new_node_str);
	}
}

static int	update_pwd_env(t_env **env, char *old_path)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), 1);
	update_env("OLDPWD", old_path, env);
	update_env("PWD", new_pwd, env);
	free(new_pwd);
	return (0);
}

static int	change_directory(char *path)
{
	if (chdir(path))
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static char	*resolve_cd_path(char **argv, t_env *env)
{
	char	*path;

	if (!argv[1])
	{
		path = get_environment(env, "HOME");
		if (!path)
			ft_printf("cd : HOME not set\n");
		return (path);
	}
	return (argv[1]);
}

int	exec_cd(char **argv, t_env *env)
{
	char	*path;
	char	*old_path;

	if (argv[1] && argv[2])
		return (ft_printf("cd : too many arguments\n"), 1);
	path = resolve_cd_path(argv, env);
	if (!path)
		return (1);
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (perror("getcwd"), 1);
	if (change_directory(path))
		return (free(old_path), 1);
	if (update_pwd_env(&env, old_path))
		return (free(old_path), 1);
	free(old_path);
	return (0);
}
