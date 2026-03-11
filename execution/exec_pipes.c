/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:59:27 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/06 16:59:27 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Após a criação do filho esquerdo, ele não vai ler no pipe apenas escrever
 dup2(oldfd, newfd) faz o STDOUT_FILENO apontar para pipefd[1]
 Quando o comando escrever no stdout, na verdade estara escrevendo dentro do pipe*/
static void exec_pipe_left(int *pipefd, t_ast *node, char **envp)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_ast_tree(node->left, envp);
	exit (1);
}

static void exec_pipe_right(int *pipefd, t_ast *node, char **envp)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exec_ast_tree(node->right, envp);
	exit (1);

}
/* Fecha o pipefd corretamente em caso de erro
*/
static int	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}
/* O pipe cria um canal de comunicação entre processos
pipe(pipefd) cria dois file descriptors:
 pipefd[2] -> fd[0] = leitura, fd[1] = escrita
*/
int exec_pipe(t_ast *node, char **envp)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid_left = fork();
	if (pid_left < 0)
		return (close_pipes(pipefd));
	if (pid_left == 0)
		exec_pipe_left(pipefd, node, envp);
	pid_right = fork();
	if (pid_right < 0)
		return (close_pipes(pipefd));
	if (pid_right == 0)
		exec_pipe_right(pipefd, node, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return(WEXITSTATUS(status));
}
