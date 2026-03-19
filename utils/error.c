/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:43 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/19 16:01:49 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *cmd, char *detail, char *msg, int error_nbr)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (detail != NULL)
	{
		ft_putstr_fd(detail, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg != NULL)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (error_nbr);
}
