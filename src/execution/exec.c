/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:57:33 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/30 10:42:08 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* vai dar execve no processo filho, retornar erro se der algo errado no 
processo/ o filho não morreu no execve
Códigos de Saída:
126 = Comando encontrado mas não executável
127 = Comando não encontrado 
*/
static void	execute_child(char *path, char **argv, t_env *env)
{
	char	**envp;
	int		saved_errno;

	envp = env_to_array(env);
	execve(path, argv, envp);
	saved_errno = errno;
	perror("minishell");
	free(path);
	free_env_array(envp);
	if (saved_errno == EACCES || saved_errno == EISDIR)
		exit(126);
	exit(127);
}

/*  vai usar execve para executar os comandos e usar o fork para criar 
uma cópia do processo
retornos de fork:
pid < 0 (negativo) falha
pid == 0 (zero) processo FILHO
pid > 0 (positivo) processo PAI
*/
void	exec_simple(t_ast *node, t_shell *shell)
{
	char		*path_to_exec;
	struct stat	st;

	if (!node->argv || !node->argv[0] || node->argv[0][0] == '\0')
		exit(0);

	// CASO 1: comando com '/'
	if (ft_strchr(node->argv[0], '/'))
	{
		if (stat(node->argv[0], &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: Is a directory\n", 2);
			exit(126);
		}
		if (access(node->argv[0], F_OK) != 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit(127);
		}
		if (access(node->argv[0], X_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			exit(126);
		}
		execute_child(node->argv[0], node->argv, shell->lst_env);
		exit(126);
	}

	// CASO 2: comando SEM '/'
	path_to_exec = find_in_path(node->argv[0]);
	if (!path_to_exec)
	if (!path_to_exec)
		{
		if (access(node->argv[0], F_OK) == 0)
		{
			struct stat st;

			if (stat(node->argv[0], &st) == 0 && S_ISDIR(st.st_mode))
			{
				ft_putstr_fd("minishell: command not found\n", 2);
				exit(127);
			}
			if (access(node->argv[0], X_OK) != 0)
			{
				ft_putstr_fd("minishell: Permission denied\n", 2);
				exit(126);
			}
		}
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	if (node->redirs)
	{
		if (apply_redirections(node->redirs) < 0)
			exit(1);
	}

	execute_child(path_to_exec, node->argv, shell->lst_env);
	free(path_to_exec);
	exit(126);
}
