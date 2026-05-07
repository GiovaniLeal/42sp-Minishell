/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:21:10 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/07 13:07:54 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == T_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == T_REDIR_OUT)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror(redir->file);
	return (fd);
}

int	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == T_HEREDOC)
			fd = redir->heredoc_fd;
		else
		{
			fd = open_redir(redir);
		}
		if (fd < 0)
			return (-1);
		if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

int	exec_builtin_redirs(t_ast *node, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	result;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (node->redirs && apply_redirections(node->redirs) < 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	result = exec_builtins(node, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (result);
}
