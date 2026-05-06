/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:18:11 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/25 00:18:11 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token_list)
{
	t_token	*current_node;

	while (token_list)
	{
		current_node = token_list->next;
		if (token_list->value)
			free(token_list->value);
		free(token_list);
		token_list = current_node;
	}
}

t_token	*ft_lst_last_node(t_token *lst_tokens)
{
	if (!lst_tokens)
		return (NULL);
	while (lst_tokens->next != NULL)
		lst_tokens = lst_tokens->next;
	return (lst_tokens);
}

void	add_back_token_lst(t_token **lst_tokens, t_token *new_token)
{
	t_token	*last_node;

	if (!lst_tokens || !new_token)
		return ;
	if (*lst_tokens == NULL)
		*lst_tokens = new_token;
	else
	{
		last_node = ft_lst_last_node(*lst_tokens);
		last_node->next = new_token;
	}
}
