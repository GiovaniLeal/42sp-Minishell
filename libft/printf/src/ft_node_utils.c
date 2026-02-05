/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:36:56 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:36:56 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/* NODE CREATE - CREATES A NEW NODE WITH A COPY OF THE GIVEN STRING           */
/* ************************************************************************** */
t_node	*ft_node_create(const char *str, size_t len)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->str_content = malloc(len + 1);
	if (!new_node->str_content)
	{
		free(new_node);
		return (NULL);
	}
	ft_memcpy(new_node->str_content, str, len);
	new_node->str_content[len] = '\0';
	new_node->len = len;
	new_node->next = NULL;
	return (new_node);
}

/* ************************************************************************** */
/* ADD LITERAL NODE - CREATES A NODE FROM A LITERAL SUBSTRING AND APPENDS IT  */
/* ************************************************************************** */
void	ft_add_literal_node(t_node **head, const char *start, size_t len)
{
	t_node	*new_node;

	new_node = ft_node_create(start, len);
	if (new_node)
		ft_list_append(head, new_node);
}
