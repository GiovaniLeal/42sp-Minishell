/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:25:56 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/05 16:36:45 by giodos-s         ###   ########.fr       */
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
