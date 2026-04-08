/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/08 13:16:23 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "environment.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

char	*find_in_path(char	*cmd);
void	exec_simple(t_ast *node, t_shell *shell);
int		apply_redirections(t_redir *redir);
int		exec_ast_tree(t_ast *node, t_shell *shell);
void	free_split(char **array);
int		exec_pipe(t_ast *node, t_shell *shell);
int		apply_heredocs(t_ast *node);
int		heredoc(char *delimiter);
int		close_fd(int fd, char *line, char *filename);

#endif