/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:36:07 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/28 17:36:03 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char	**env_arr)
{
	int		i;

	i = 0;
	while (env_arr[i])
	{
		ft_printf("declare -x ");
		ft_printf("%s\n", env_arr[i++]);
	}
}

void	sort_arr(char **export_arr)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (export_arr[j])
	{
		i = 0;
		while (export_arr[i] && export_arr[i + 1])
		{
			if (ft_strcmp(export_arr[i], export_arr[i + 1]) > 0)
			{
				temp = export_arr[i];
				export_arr[i] = export_arr[i + 1];
				export_arr[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

int	display_export(t_env *env)
{
	char	**export_arr;

	export_arr = env_to_array(env);
	sort_arr(export_arr);
	print_env(export_arr);
	free_env_array(export_arr);
	return (0);
}
