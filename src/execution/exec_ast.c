/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:00:29 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/05 09:15:04 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Interprets the status returned by waitpid to extract the correct exit code.

   - If the process exited normally → return exit status (high 8 bits)
   - If terminated by a signal → return 128 + signal number

   Bitwise details:
   - 0x7F masks the lower 7 bits (signal information)
   - 0xFF extracts one byte (exit status)
*/
static int	exit_status(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	return (128 + (status & 0x7F));
}

/* Executes a command in a forked child process.

   - fork():
     pid < 0 → fork failed
     pid == 0 → child process
     pid > 0 → parent process

   Child process:
   - Restores default signal behavior (SIGINT, SIGQUIT)
   - Executes the command via exec_simple
   - Exits with 127 if execution fails

   Parent process:
   - Waits for the child to finish (waitpid)
   - Restores shell signal handlers
   - Returns the normalized exit status
*/

// if (is_directory(node->argv[0]) && !node->argv[1])
// 	{
// 		ft_putstr_fd("minishell: Is a directory\n", 2);
// 		shell->last_exit = 126;
// 		return (shell->last_exit);
// 	}
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
		exit (shell->last_exit);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	return (exit_status(status));
}

/* Executes an AST node based on its type.

   - Returns immediately if the node is NULL or an empty command
   - If the node is a PIPE → delegates to exec_pipe
   - Ignores SIGINT and SIGQUIT in the parent during execution

   Builtins:
   - If the command is a builtin → executes without fork
   - Applies redirections if needed

   External commands:
   - Executed via fork (exec_forked)

   Updates shell->last_exit with the resulting exit status
*/
int	exec_ast_tree(t_ast *node, t_shell *shell)
{
	int	result;

	if (!node)
		return (0);
	if (node->type == NODE_CMD
		&& (!node->argv || !node->argv[0]))
		return (0);
	if (node->type == NODE_PIPE)
	{
		result = exec_pipe(node, shell);
		shell->last_exit = result;
		return (result);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (its_builtin(node))
	{
		result = exec_builtin_redirs(node, shell);
		shell->last_exit = result;
		return (result);
	}
	result = exec_forked(node, shell);
	shell->last_exit = result;
	return (result);
}

int is_directory(const char *path)
{
    struct stat st;

    if (stat(path, &st) == -1)
        return 0;
    return S_ISDIR(st.st_mode);
}
