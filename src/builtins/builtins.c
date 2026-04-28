/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:35:07 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/28 08:46:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*  	    Dispatcher for shell built-in commands: 	        */
/*   1. Identifies if the given command matches an internal shell function.   */
/*   2. Executes the corresponding function (e.g., cd, echo, exit) and        */
/*    returns its exit status.                                                */
/*   3. Returns -1 if the command is not a built-in, signaling that it        */
/*    should be handled as an external executable.                            */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*           Identifies if a command is a shell built-in:                     */
/*     1. Checks for edge cases (NULL nodes or empty arguments).              */
/*     2. Matches the command name against the list of supported built-ins    */
/*     (exit, echo, pwd, cd, env, export, unset).                             */
/*     3. Returns 1 if the command is a built-in, 0 otherwise.                */
/*     This helper allows the executor to decide between in-process execution */
/*     or forking an external executable.                                     */
/* ************************************************************************** */
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
