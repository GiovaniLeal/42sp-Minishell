/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/18 14:47:20 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

char	*find_in_path(char	*cmd);
void	exec_simple(t_ast *node, char **envp);
int		apply_redirections(t_redir *redir);
int		exec_ast_tree(t_ast *tree, char **envp);
void	free_split(char **array);
int		exec_pipe(t_ast *node, char **envp);
int		exec_builtins(t_ast *node, char **envp);
int		exec_forked(t_ast *node, char **envp);
int		ft_exit(char **argv);
int		error_msg(char *cmd, char *detail, char *msg, int error_nbr);

#endif