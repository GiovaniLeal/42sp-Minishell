/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:38:15 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/05 17:38:15 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# define PROMPT "minishell$ "

/* ************************************************************************** */
//*                          Path = /SRC/TOKENS                               */
/*         - Function declarations and their respective .c files -            */
/* ************************************************************************** */
// * lexer.c
t_token	*lexer(char *str);

// * lexer_list.c
void	free_token_list(t_token *token_list);
t_token	*ft_lst_last_node(t_token *lst_tokens);
void	add_back_token_lst(t_token **lst_tokens, t_token *new_token);

// * lexer_utils.c
int		state_status(char c);
int		is_operator(char c);
int		is_white_space(char c);
char	*skip_spaces(char *str);
#endif