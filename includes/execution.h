/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/06 16:03:26 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/* ************************************************************************** */
//*                          Path = /SRC/EXECUTION                            */
/*         - Function declarations and their respective .c files -            */
/* ************************************************************************** */
// * exec_ast.c
int		is_directory(const char *path);
int		exec_forked(t_ast *node, t_shell *shell);
int		exec_ast_tree(t_ast *node, t_shell *shell);

// * exec_pipes.c
int		exec_pipe(t_ast *node, t_shell *shell);

// * exec.c
void	handle_path_not_found(char *cmd, t_shell *shell);
void	execute_child(char *path, t_ast *node, t_env *env, t_shell *shell);
void	exec_simple(t_ast *node, t_shell *shell);

//* path.c
char	*check_absolute_path(char *cmd, t_shell *shell);
char	*search_in_dir(char	**dirs, char *cmd);
char	*find_in_path(char *cmd, t_shell *shell);
void	handle_path_command(t_ast *node, t_shell *shell);

/* ************************************************************************** */
//*                          Path = /SRC/REDIR                                */
/*         - Function declarations and their respective .c files -            */
/* ************************************************************************** */
// * heredoc_utils.c
int		apply_heredocs(t_ast *node);
int		close_fd(int fd, char *line, char *filename);

// * heredoc.c
int		heredoc(char *delimiter);

// * redir.c
int		apply_redirections(t_redir *redir);
int		exec_builtin_redirs(t_ast *node, t_shell *shell);
#endif