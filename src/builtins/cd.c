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

/* ************************************************************************** */
/*          		Function Prototypes 		        */
/* ************************************************************************** */
int				exec_cd(char **argv, t_env *env);
static char		*resolve_cd_path(char **argv, t_env *env);
static int		update_pwd_env(t_env **env, char *old_path);
static void		update_env(char *key, char *path, t_env **lst_env);
static t_env	*find_node(char *key, t_env *lst_env);

/* ************************************************************************** */
/*             Executes the 'cd' (change directory) built-in:                 */
/* 1. Validates arguments (strictly handles only one target path).            */
/* 2. Resolves the destination path (interpreting HOME or relative paths).    */
/* 3. Captures the current working directory to update OLDPWD later.          */
/* 4. Performs the directory change using chdir() and handles system errors.  */
/* 5. Updates PWD and OLDPWD environment variables to reflect the change.     */
/* ************************************************************************** */
int	exec_cd(char **argv, t_env *env)
{
	char	*path;
	char	*old_path;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd(" too many arguments", 2);
		return (1);
	}
	path = resolve_cd_path(argv, env);
	if (!path)
		return (1);
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (perror("getcwd"), 1);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_path);
		return (1);
	}
	if (update_pwd_env(&env, old_path))
		return (free(old_path), 1);
	free(old_path);
	return (0);
}

/* ************************************************************************** */
/*  	Resolves the target destination for the 'cd' command:           */
/* 1. If no argument is provided (cd alone), it attempts to retrieve the      */
/* "HOME" environment variable as a fallback.                                 */
/* 2. If "HOME" is missing from the environment, displays an error message.   */
/* 3. If an argument is present, it returns it as the primary target path.    */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*      Synchronizes environment variables after a directory change:          */
/*    1. Captures the new absolute path using getcwd().                       */
/*    2. Updates "OLDPWD" with the previous directory path.                   */
/*    3. Updates "PWD" with the newly acquired current path.                  */
/*    4. Frees the temporary buffer to prevent memory leaks.                  */
/*    Returns 0 on success, or 1 if getcwd fails.                             */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*             Updates or inserts an environment variable (Upsert):           */
/*  1. Searches for an existing node matching the given key.                  */
/*  2. If found: Updates the value by freeing the old string and              */
/*  allocating a new duplicate of the provided path.                          */
/*  3. If not found: Constructs a new "KEY=VALUE" string, creates a new       */
/*  environment node, and appends it to the linked list.                      */
/*  Note: Handles memory allocation carefully to prevent leaks.               */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*       Searches for a specific key in the environment linked list:          */
/*   1. Starts at the beginning of the list and iterates through each node.   */
/*   2. Compares the current node's key with the target key using ft_strcmp.  */
/*   3. Returns the pointer to the node if a match is found.                  */
/*   4. Returns NULL if the end of the list is reached without a match.       */
/* ************************************************************************** */
static t_env	*find_node(char *key, t_env *lst_env)
{
	t_env	*temp_node;

	temp_node = lst_env;
	while (temp_node && ft_strcmp(temp_node->key, key) != 0)
		temp_node = temp_node->next;
	return (temp_node);
}
