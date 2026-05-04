/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/04 20:07:46 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

// ---------------------------------------------------------- exec.c
void	execute_child(char *path, char **argv, t_env *env);
void	exec_simple(t_ast *node, t_shell *shell);

// ---------------------------------------------------------- exec_ast.c
int		exec_ast_tree(t_ast *node, t_shell *shell);
int		exec_forked(t_ast *node, t_shell *shell);

// ---------------------------------------------------------- exec_pipes.c
int		exec_pipe(t_ast *node, t_shell *shell);

// ---------------------------------------------------------- path.c
char	*find_in_path(char *cmd, t_shell * shell);
int	handle_path_command(t_ast *node, t_shell *shell);
void	handle_path_not_found(char *cmd);
char	*check_absolute_path(char *cmd, t_shell *shell);

// ---------------------------------------------------------- redir.c
int		apply_redirections(t_redir *redir);
int		exec_builtin_redirs(t_ast *node, t_shell *shell);

// -------------------------------------------------------heredoc.c
int		heredoc(char *delimiter);

// -------------------------------------------------------heredoc_utils.c
int		close_fd(int fd, char *line, char *filename);
int		apply_heredocs(t_ast *node);

// FUNCAO TESTE
int is_directory(const char *path);
#endif