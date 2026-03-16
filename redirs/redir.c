/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:21:10 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/25 15:07:15 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* vai retornar qual o fd(arquivo) a ser usado e quais serão 
as permissões do arquivo de acordo com o sinal usado:

(redirecionamento de entrada) < - somente leitura
(truncate) > - cria o arquivo, escreve nele, apaga o que ja tinha
(append) >> - cria o arquivo, escreve nele, mantem o que ja tinha
*/
static int	open_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == T_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == T_REDIR_OUT)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror(redir->file);
	return (fd);
}

int	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = open_redir(redir);
		if (fd < 0)
			return (-1);
		if (redir->type == T_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
