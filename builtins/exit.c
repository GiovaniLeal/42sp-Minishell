/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:54:06 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/18 15:06:38 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv)
{
	int	i;

	i = 0;
	if (argv[2])
		return (error_msg(argv[0], NULL, "too many arguments", 2));
	else
	{
		while (ft_isalnum(argv[1][i]))
			i++;
		
	}
}