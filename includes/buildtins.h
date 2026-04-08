/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:25:56 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/07 00:07:53 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_ast *node, t_shell *shell);
int	ft_exit(char **argv);
int	is_numeric(char	*str);

int exec_echo(char **str_array);
int	exec_pwd(char **argv);
int	exec_cd(char **argv, t_env *env);


int	exec_env(char **argv, t_env *env);

int     exec_export(char **argv, t_shell  *env);
int	    is_valid_arg(char *str);

int     display_export(t_env *env);
void	sort_arr(char **export_arr);
void	print_env(char	**env_arr);
t_env	*find_in_lst(char *str, t_env *env);
void	export_update(t_env *node, char *str);