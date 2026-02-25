/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:57:33 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/25 15:05:35 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* vai dar execve no processo filho, retornar erro se der algo errado no 
processo/ o filho não morreu no execve
Códigos de Saída:
126 = Comando encontrado mas não executável
127 = Comando não encontrado 
*/
static void	execute_child(char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	perror("minishell");
	free(path);
	if (errno == EACCES)
		exit(126);
	exit(127);
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

/*  vai usar execve para executar os comandos e usar o fork para criar 
uma cópia do processo
retornos de fork:
pid < 0 (negativo) falha
pid == 0 (zero) processo FILHO
pid > 0 (positivo) processo PAI
*/
int	exec_simple(t_ast *node, char **envp)
{
	char	*path_to_exec;
	pid_t	pid;
	int		status;

	path_to_exec = find_in_path(node->argv[0]);
	if (!path_to_exec)
		return (127);
	pid = fork();
	if (pid < 0)
	{
		free(path_to_exec);
		return (-1);
	}
	if (pid == 0)
	{
		if (node->redirs)
		{
			if (apply_redirections(node->redirs) < 0)
				exit (1);
		}
		execute_child(path_to_exec, node->argv, envp);
	}
	free(path_to_exec);
	waitpid(pid, &status, 0);
	return (exit_status(status));
}
