/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 19:29:07 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/02 19:29:07 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **argv)
{
	char	*cwd;

	if (argv[1])
	{
		ft_printf("pwd : too many arguments\n", STDERR_FILENO);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
