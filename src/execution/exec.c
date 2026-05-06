/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:57:33 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/06 12:42:18 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_path_not_found(char *cmd, t_shell *shell)
{
	(void)cmd;
	ft_putstr_fd("minishell : command not found\n", 2);
	shell->last_exit = 127;
}

void	execute_child(char *path, t_ast *node, t_env *env, t_shell *shell)
{
	char	**envp;
	int		saved_errno;

	envp = env_to_array(env);
	if (!envp)
		clear_and_exit(shell, 1);
	execve(path, node->argv, envp);
	saved_errno = errno;
	free_env_array(envp);
	if (saved_errno == EACCES || saved_errno == EISDIR)
		shell->last_exit = 126;
	else
		shell->last_exit = 127;
	clear_and_exit(shell, shell->last_exit);
}

static void	path_checker(t_ast *node, t_shell *shell)
{
	struct stat	file_info;

	if (stat(node->argv[0], &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
			handle_path_not_found(node->argv[0], shell);
		else if (access(node->argv[0], X_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			clear_and_exit(shell, 126);
		}
		else
		{
			execute_child(node->argv[0], node, shell->lst_env, shell);
		}
	}
	else
	{
		handle_path_not_found(node->argv[0], shell);
		clear_and_exit(shell, shell->last_exit);
	}
}

void	exec_simple(t_ast *node, t_shell *shell)
{
	char		*path_to_exec;

	if (!node->argv || !node->argv[0] || node->argv[0][0] == '\0')
		exit(0);
	if (ft_strchr(node->argv[0], '/'))
	{
		handle_path_command(node, shell);
		clear_and_exit(shell, shell->last_exit);
	}
	path_to_exec = find_in_path(node->argv[0], shell);
	if (!path_to_exec)
		path_checker(node, shell);
	if (node->redirs && apply_redirections(node->redirs) < 0)
	{
		free(path_to_exec);
		clear_and_exit(shell, 1);
	}
	execute_child(path_to_exec, node, shell->lst_env, shell);
	clear_and_exit(shell, shell->last_exit);
}
