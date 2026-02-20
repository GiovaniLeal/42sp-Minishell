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

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/* ************************************************************************** */
/*  		     TOKEN PART - ENUM AND LIST	        	        */
/* ************************************************************************** */
/* 							        */
/* Esse enum simplifica a implementacao do lexer quanto a aspas simples e duplas*/
typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}	t_state;
/* 							        */
/*   Esse enum representa os operadores(tokens) esperados do nosso shell.     */
/*EX.:		T_WORD :     "echo " 		                  */
/*EX.:		T_PIPE :     " |   " 	         		        */
/*EX.:		T_REDIR_IN : " <   " 		        	        */
/*EX.:		T_REDIR_OUT: " >   " 			        */
/*EX.:		T_APPEND :   " >>  " 		                  */
/*EX.:		T_HEREDOC :  " <<  "		                  */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

/* Armazenamos todos os comandos recebidos na struct abaixo em lista        */
typedef struct s_token
{ 
	char		*value;
	t_token_type	type;
	struct s_token		*next;	
}	t_token;


/* ************************************************************************** */






int	main(void);

/* lexer.c ---------------------------------------------*/
t_token	*lexer(char *str);


/* lexer_utils.c ---------------------------------------------*/
int	state_status(char c);
int	is_operator(char c);
int	is_white_space(char c);
void	free_token_list(t_token *token_list);
t_token	*ft_lst_last_node(t_token *lst_tokens);
void	add_back_token_lst(t_token **lst_tokens, t_token *new_token);


/* EXCLUIR ANTES DO ENVIO - lexer_tester.c -------------*/
void	print_tokens(t_token  *tokens_list);
char	*token_type_to_str(t_token_type type);
