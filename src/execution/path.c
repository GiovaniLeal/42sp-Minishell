/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:23:11 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/05 14:20:11 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*check_absolute_path(char *cmd, t_shell *shell)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			shell->last_exit = 127;
			return (NULL);
		}
		if (access(cmd, X_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			shell->last_exit = 126;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*search_in_dir(char	**dirs, char *cmd)
{
	char	*temp;
	char	*path_candidate;
	int		i;

	i = 0;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		path_candidate = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_candidate, X_OK) == 0)
		{
			free_split(dirs);
			return (path_candidate);
		}
		free(path_candidate);
		i++;
	}
	free_split(dirs);
	return (NULL);
}

char	*find_in_path(char *cmd, t_shell * shell)
{
	char	*path;
	char	**dirs;
	char	*result;

	(void)shell;
	// result = check_absolute_path(cmd, shell);
	// if (result)
	// 	return (result);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	result = search_in_dir(dirs, cmd);
	return (result);
}

void	handle_path_command(t_ast *node, t_shell *shell)
{
	struct stat	st;

	if (stat(node->argv[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: Is a directory\n", 2);
		shell->last_exit = 126;
		
	}
	else if (access(node->argv[0], F_OK) != 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		shell->last_exit = 127;
		
	}
	else if (access(node->argv[0], X_OK) != 0)
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		shell->last_exit = 126;
		
	}
	execute_child(node->argv[0], node, shell->lst_env, shell);
}


void	exit_status(t_ast *node, t_shell *shell, char *str_error, int exit_number)
{
	write(2, str_error, ft_strlen(str_error));
	shell->last_exit = exit_number;
	free_ast(node);
	free_env_list(shell->lst_env);
}


void	handle_path_not_found(char *cmd, t_shell *shell)
{
	 (void)cmd;
	ft_putstr_fd("minishell : command not found\n", 2);
	shell->last_exit = 127;
}
