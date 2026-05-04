/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:25:56 by giodos-s          #+#    #+#             */
/*   Updated: 2026/05/04 18:51:46 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

// -------------------------------------------------> builtins.c
int			exec_builtins(t_ast *node, t_shell *shell);
int			its_builtin(t_ast *node);

// -------------------------------------------------> cd.c
int			exec_cd(char **argv, t_env *env);

// -------------------------------------------------> echo.c
int			exec_echo(char **str_array);

// -------------------------------------------------> env.c
int			exec_env(char **argv, t_env *env);

// -------------------------------------------------> exit.c
int			ft_exit(char **argv, t_shell *shell);
int			is_numeric(char	*str);

// -------------------------------------------------> export.c
int			exec_export(char **argv, t_shell *shell);
int			is_valid_arg(char *str);
t_env		*find_in_lst(char *str, t_env *env);
// -------------------------------------------------> export_display.c
void		export_update(t_env *node, char *str);
void		print_env(char	**env_arr);
void		sort_arr(char **export_arr);
int			display_export(t_env *env);

// -------------------------------------------------> pwd.c
int			exec_pwd(char **argv);

// -------------------------------------------------> unset.c
int			exec_unset(char **argv, t_shell *shell);

#endif