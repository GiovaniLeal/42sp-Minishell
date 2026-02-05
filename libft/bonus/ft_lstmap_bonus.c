/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:16:34 by giodos-s          #+#    #+#             */
/*   Updated: 2025/11/08 20:09:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap_bonus(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*head;

	temp = NULL;
	head = NULL;
	if (!lst)
		return (NULL);
	head = ft_lstnew_bonus(f(lst->content));
	if (!head)
		return (NULL);
	temp = head;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew_bonus(f(lst->content));
		if (!temp->next)
		{
			ft_lstclear_bonus(&head, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (head);
}
