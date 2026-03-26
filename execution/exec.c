/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:57:33 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/26 17:46:52 by giodos-s         ###   ########.fr       */
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

	envp = env_to_array(env);
	execve(path, argv, envp);
	perror("minishell");
	free(path);
	if (errno == EACCES)
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
void exec_simple(t_ast *node, t_shell *shell)
{
    char *path_to_exec;

    path_to_exec = find_in_path(node->argv[0]);
    if (!path_to_exec)
    {
        perror("command not found");
        exit(127);
    }

    if (node->redirs)
    {
        if (apply_redirections(node->redirs) < 0)
            exit(1);
    }

    execute_child(path_to_exec, node->argv, shell->lst_env);
}
