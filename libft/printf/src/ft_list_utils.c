/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:39:27 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:39:27 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/* LIST CLEAR - FREES ALL NODES AND CONTENTS IN THE LIST                      */
/* ************************************************************************** */
void	ft_list_clear(t_node **head)
{
	t_node	*current;
	t_node	*next_node;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next_node = current->next;
		free(current->str_content);
		free(current);
		current = next_node;
	}
	*head = NULL;
}

/* ************************************************************************** */
/* LIST APPEND - ADDS A NEW NODE AT THE END OF THE LIST                       */
/* ************************************************************************** */
void	ft_list_append(t_node **head, t_node *new_node)
{
	t_node	*current;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
