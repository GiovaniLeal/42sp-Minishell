/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:13:54 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/31 17:17:35 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_option(char **str_array)
{
    int count;

    count = 0;
    while (str_array[count] && ft_strcmp(str_array[count], "-n") == 0)
    {
        count++;
    }
    return (count);
}

int exec_echo(char **str_array)
{
    int i;
    int has_n_option;

    i = 1;
    has_n_option = check_option(str_array);

    if (has_n_option)
    {
        while (str_array[has_n_option + i])
        {
            ft_printf("%s", str_array);
            has_n_option++;
        }
    }
    else
    {
        while (str_array[i])
        {
            ft_printf("%s ", str_array[i]);
            i++;
        }
        ft_printf("\n");
    }   
    return (0);
}
