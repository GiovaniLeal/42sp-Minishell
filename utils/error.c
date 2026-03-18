/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:43 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/18 14:44:46 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *cmd, char *detail, char *msg, int error_nbr)
{
	ft_putstr("minishell: ", 2);
	ft_putstr(cmd, 2);
	ft_pustr(": ", 2);
	if (detail != NULL)
	{
		ft_putstr(detail, 2);
		ft_putstr(": ", 2);
	}
	if (msg != NULL)
		ft_putstr(msg, 2);
	ft_putstr("\n", 2);
	return (error_nbr);
}
