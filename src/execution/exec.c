/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:57:33 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/04 11:20:15 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* Executes a command in the child process using execve.
   If execve fails, it handles the error, frees allocated memory,
   and exits with the appropriate status code.

Exit codes:
126 → Command found but not executable (e.g., permission denied, is a directory)
127 → Command not found or execve failed                                      */
/* ************************************************************************** */
void	execute_child(char *path, char **argv, t_env *env)
{
	char	**envp;
	int		saved_errno;

	envp = env_to_array(env);
	execve(path, argv, envp);
	saved_errno = errno;
	perror("minishell");
	free(path);
	free_env_array(envp);
	if (saved_errno == EACCES || saved_errno == EISDIR)
		exit(126);
	exit(127);
}

/* ************************************************************************** */
/* Handles execution of a simple command node.

   - Validates the command input
   - Detects if the command contains a '/' (absolute or relative path)
   - Resolves the executable path using PATH when needed
   - Applies redirections if present
   - Delegates execution to the child process (execve)

   Note:
   This function is intended to run inside a forked child process.            */
/* ************************************************************************** */
void	exec_simple(t_ast *node, t_shell *shell)
{
	char	*path_to_exec;

	if (!node->argv || !node->argv[0] || node->argv[0][0] == '\0')
		exit(0);
	if (ft_strchr(node->argv[0], '/'))
		handle_path_command(node, shell);
	path_to_exec = find_in_path(node->argv[0]);
	if (!path_to_exec)
		handle_path_not_found(node->argv[0]);
	if (node->redirs && apply_redirections(node->redirs) < 0)
		exit(1);
	execute_child(path_to_exec, node->argv, shell->lst_env);
	free(path_to_exec);
	exit(126);
}
