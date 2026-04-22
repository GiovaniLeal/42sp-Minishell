/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:35:07 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/17 15:41:30 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_ast *node, t_shell *shell)
{
	if (ft_strcmp(node->argv[0], "exit") == 0)
		return (ft_exit(node->argv, shell));
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
	if (ft_strcmp(node->argv[0], "unset") == 0)
		return (exec_unset(node->argv, shell));
	return (-1);
}

int	its_builtin(t_ast *node)
{
	if (!node || !node->argv || !node->argv[0])
		return (0);
	if (!ft_strcmp(node->argv[0], "exit")
		|| !ft_strcmp(node->argv[0], "echo")
		|| !ft_strcmp(node->argv[0], "pwd")
		|| !ft_strcmp(node->argv[0], "cd")
		|| !ft_strcmp(node->argv[0], "env")
		|| !ft_strcmp(node->argv[0], "export")
		|| !ft_strcmp(node->argv[0], "unset"))
		return (1);
	return (0);
}
