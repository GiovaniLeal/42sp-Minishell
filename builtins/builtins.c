/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:35:07 by anunes-o          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/08 15:23:05 by anunes-o         ###   ########.fr       */
=======
/*   Updated: 2026/04/05 16:36:14 by giodos-s         ###   ########.fr       */
>>>>>>> c46718227e7b3ac172636ed60055266badad4556
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_ast *node, t_shell *shell)
{
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
	return (-1);
}
