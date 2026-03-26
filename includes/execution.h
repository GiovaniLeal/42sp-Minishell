/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/26 19:36:49 by giodos-s         ###   ########.fr       */
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
int 	exec_ast_tree(t_ast *node, t_shell *shell);
void	free_split(char **array);
int exec_pipe(t_ast *node, t_shell *shell);

#endif