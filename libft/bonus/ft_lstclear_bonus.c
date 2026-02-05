/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:24:00 by giodos-s          #+#    #+#             */
/*   Updated: 2025/11/08 20:09:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* LIST CLEAR - Deletes and frees the given node and all its sucessors        */
/* ************************************************************************** */
void	ft_lstclear_bonus(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = NULL;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	free(temp);
}
