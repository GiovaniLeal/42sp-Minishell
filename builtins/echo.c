/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:13:54 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/31 15:48:50 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_echo_n(t_ast *node)
{
    (void)node;
    return (1);
}

int exec_simple_echo(t_ast *node)
{
    while (node->next != null)
    {int exec_echo(t_ast *node)
        ft_printf("%s ", node);
        node = node->next;
    }
    ft_printf("%s\n", node);
    return(0);
}


//Identifica se possui a opcao [ -n ] - retorna 0 se nao encontrar opcao e 1 se encontrar.
int echo_option(t_ast *node)
{
    while (node[0] != '-' && node[1] != 'n')
    {
        if (node->next == NULL)
            return (0) 
        node = node->next;
    }
    return (1);
}


int exec_echo(t_ast *node)
{
    if (echo_option(node))
        return (exec_echo_n(node));
    return (exec_simple_echo(node));
}