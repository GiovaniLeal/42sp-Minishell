/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:57:33 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/05 09:26:00 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute_child(char *path, char **argv, t_env *env, t_shell *shell)
{
	char	**envp;
	int		saved_errno;

	envp = env_to_array(env);
	if (!envp)
		exit(1);
	execve(path, argv, envp);
	saved_errno = errno;
	//free(path);
	free_env_array(envp);
	if (saved_errno == EACCES || saved_errno == EISDIR)
		shell->last_exit = 126;
	else
		shell->last_exit = 127;
	exit (shell->last_exit);

}


void	exec_simple(t_ast *node, t_shell *shell)
{
	char	*path_to_exec;

	if (!node->argv || !node->argv[0] || node->argv[0][0] == '\0')
		exit(0);
	// 🔴 CASO 1: comando com '/'
	if (ft_strchr(node->argv[0], '/'))
	{
		handle_path_command(node, shell);
		free(node);
		free(shell->lst_env);
		exit(shell->last_exit);
	}
	// 🔴 CASO 2: comando normal → PATH
	path_to_exec = find_in_path(node->argv[0], shell);
	if (!path_to_exec)
	{
		struct stat	st;

		if (stat(node->argv[0], &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
				handle_path_not_found(node->argv[0], shell);
			else if (access(node->argv[0], X_OK) != 0)
			{
				ft_putstr_fd("minishell: Permission denied\n", 2);
				shell->last_exit = 126;
			}
			else
			{
				// existe e é executável, mas não está no PATH
				execute_child(node->argv[0], node->argv, shell->lst_env, shell);
			}
		}
		else
		{
			handle_path_not_found(node->argv[0], shell);
		}

		free_ast(node);
		free_env_list(shell->lst_env);
		exit(shell->last_exit);
	}
	// 🔴 redirections
	if (node->redirs && apply_redirections(node->redirs) < 0)
	{
		free_ast(node);
		free_env_list(shell->lst_env);
		free(path_to_exec);
		exit(1);
	}
	// 🔴 execve (não retorna se der certo)
	execute_child(path_to_exec, node->argv, shell->lst_env, shell);
	// 🔴 fallback (execve falhou)
	free_ast(node);
	free_env_list(shell->lst_env);
	exit(shell->last_exit);
}
