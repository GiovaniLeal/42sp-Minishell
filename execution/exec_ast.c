/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:00:29 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/16 16:39:12 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_node(t_ast *node, char **envp)
{
	if (!node || !node->argv || !node->argv[0])
		return (0);
	exec_simple(node, envp);
	return (0);
}

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

/*IMPORTANTE = Aqui precisamos atualizar a assinatura para receber T_SHELL
 T_shell guarda uma lista(cópia) de envp. É sobre ela que 
 realizaremos a execuçâo*/
int	exec_ast_tree(t_ast *node, char **envp)
{
	int		result;

	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, envp));
	if (node->type == NODE_CMD)
	{
		result = exec_builtins(node, envp);
		if (result != -1)
			return (result);
		return (exec_forked(node, envp));
	}
	return (0);
}

int	exec_forked(t_ast *node, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		exec_node(node, envp);
		exit (1);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (exit_status(status));
	}
	return (0);
}
