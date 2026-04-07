/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:35:07 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/06 22:10:07 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_ast *node, t_shell *shell)
{
	(void)shell;
	if (ft_strcmp(node->argv[0], "exit") == 0)
		return (ft_exit(node->argv));
	if (ft_strcmp(node->argv[0], "echo") == 0)
		return (exec_echo(node->argv));
	if (ft_strcmp(node->argv[0], "pwd") == 0)
		return (exec_pwd(node->argv));
	if (ft_strcmp(node->argv[0], "cd") == 0)
		return (exec_cd(node->argv, shell->lst_env));
	if (ft_strcmp(node->argv[0], "env") == 0)
		return (exec_env(node->argv, shell->lst_env));
	if (ft_strcmp(node->argv[0], "export") == 0)
		return (exec_export(node->argv, shell));
	return (0);
}
