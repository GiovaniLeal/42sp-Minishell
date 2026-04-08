/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:00:29 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/08 14:04:58 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* vai diagnosticar qual tipo de erro ocorreu para determinar os 
códigos de saída checando o retorno em status e somando com 
(0x7F)128 (comando terminou por sinal) e
(0xFF)255 = 1111 1111, 8 bits ligados, mascara para pegar 1 byte
*/
static int	exit_status(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	return (128 + (status & 0x7F));
}


int	exec_forked(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_simple(node, shell);
		exit(127);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	return (exit_status(status));
}

int	exec_ast_tree(t_ast *node, t_shell *shell)
{
	int	result;

	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
	{
		result = exec_pipe(node, shell);
		shell->last_exit = result;
		return (result);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	result = exec_builtins(node, shell);
	if (result != -1)
	{
		shell->last_exit = result;
		return (result);
	}
	result = exec_forked(node, shell);
	shell->last_exit = result;
	return (result);
}
