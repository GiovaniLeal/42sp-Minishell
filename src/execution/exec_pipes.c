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

/* Executes the side of a pipe in a child process.

   - Closes the read end of the pipe (unused)
   - Redirects STDOUT to the pipe's write end using dup2
   - Executes the left AST subtree
   - Frees allocated resources before exiting

   After dup2, any output written to stdout will go into the pipe
*/
static void	exec_pipe_left(int *pipefd, t_ast *node, t_shell *shell)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_ast_tree(node->left, shell);
	clear_and_exit(shell, shell->last_exit);
}

static void	exec_pipe_right(int *pipefd, t_ast *node, t_shell *shell)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exec_ast_tree(node->right, shell);
	clear_and_exit(shell, shell->last_exit);
}

static int	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}

/* Executes a pipeline between two commands.

   - pipe() creates a unidirectional communication channel:
     pipefd[0] → read end
     pipefd[1] → write end

   - Forks two child processes:
     • Left child → writes to the pipe
     • Right child → reads from the pipe

   - Parent process:
     • Closes both pipe ends
     • Waits for both children to finish
     • Returns the exit status of the right command (shell behavior)
*/
int	exec_pipe(t_ast *node, t_shell *shell)
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
		exec_pipe_left(pipefd, node, shell);
	pid_right = fork();
	if (pid_right < 0)
		return (close_pipes(pipefd));
	if (pid_right == 0)
		exec_pipe_right(pipefd, node, shell);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}
