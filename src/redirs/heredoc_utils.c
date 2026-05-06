/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:16:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/06 15:23:37 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_heredocs_pipe(t_ast *node)
{
	if (apply_heredocs(node->left) < 0)
		return (-1);
	if (apply_heredocs(node->right) < 0)
		return (-1);
	return (0);
}

int	apply_heredocs(t_ast *node)
{
	t_redir	*tmp;
	int		fd;

	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (apply_heredocs_pipe(node));
	else
	{
		tmp = node->redirs;
		while (tmp)
		{
			if (tmp->type == T_HEREDOC)
			{
				fd = heredoc(tmp->file);
				if (fd < 0)
					return (-1);
				tmp->heredoc_fd = fd;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	close_fd(int fd, char *line, char *filename)
{
	if (line)
		free(line);
	close(fd);
	unlink(filename);
	free(filename);
	return (-1);
}
