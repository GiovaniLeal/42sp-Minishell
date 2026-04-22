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
/*         		      STRUCTS   	                      */
/* T_TOKEN = Storages all comands in a list of tokens		        */
/* T_STATE = For control of the literal quotes                                */
/* T_TOKEN_TYPE = Types of comands tokens			        */
/* ************************************************************************** */

typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}	t_state;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;	
}	t_token;

/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

/* lexer.c -------------------------------------------------------------------*/
t_token	*lexer(char *str);

/* lexer_list.c --------------------------------------------------------------*/
void	free_token_list(t_token *token_list);
t_token	*ft_lst_last_node(t_token *lst_tokens);
void	add_back_token_lst(t_token **lst_tokens, t_token *new_token);

/* lexer_utils.c -------------------------------------------------------------*/
int		state_status(char c);
int		is_operator(char c);
int		is_white_space(char c);
char	*skip_spaces(char *str);

#endif