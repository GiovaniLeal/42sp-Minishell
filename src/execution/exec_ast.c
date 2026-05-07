/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:00:29 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/07 13:55:26 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_status(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	return (128 + (status & 0x7F));
}

int	exec_forked(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_simple(node, shell);
		clear_and_exit(shell, shell->last_exit);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	return (exit_status(status));
}

int	exec_ast_tree(t_ast *node, t_shell *shell)
{
	int	result;

	if (!node)
		return (0);
	if (node->type == NODE_CMD
		&& (!node->argv || !node->argv[0]))
		return (0);
	if (node->type == NODE_PIPE)
	{
		result = exec_pipe(node, shell);
		shell->last_exit = result;
		return (result);
	}
	signal(SIGQUIT, SIG_IGN);
	if (its_builtin(node))
	{
		result = exec_builtin_redirs(node, shell);
		shell->last_exit = result;
		return (result);
	}
	result = exec_forked(node, shell);
	shell->last_exit = result;
	return (result);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}
