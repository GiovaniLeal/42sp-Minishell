/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:34:03 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/11 15:44:24 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_heredocs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == T_HEREDOC)
			process_heredocs(redir);
		redir = redir->next;
	}
}

int	process_heredocs(t_redir *redir)
{
	
}