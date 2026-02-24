/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:21:10 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/24 16:18:03 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* vai retornar qual o fd(arquivo) a ser usado e quais serão 
as permissões do arquivo de acordo com o sinal usado:

(redirecionamento de entrada) < - somente leitura
(truncate) > - cria o arquivo, escreve nele, apaga o que ja tinha
(append) >> - cria o arquivo, escreve nele, mantem o que ja tinha
*/
int	open_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == T_REDIR_IN)
		fd = open(redir->target, O_RDONLY);
	else if (redir->type == T_REDIR_OUT)
		fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror(redir->target);
	return (fd);
}
