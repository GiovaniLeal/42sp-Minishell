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

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include "execution.h"
# include "types.h"

// /* ************************************************************************** */
// /*  		     TOKEN PART - ENUM AND LIST	        	        */
// /* ************************************************************************** */
// /* 							        */
// /*   Esse enum representa os operadores(tokens) esperados do nosso shell.     */
// /*EX.:		T_WORD :     "echo " 		                  */
// /*EX.:		T_PIPE :     " |   " 	         		        */
// /*EX.:		T_REDIR_IN : " <   " 		        	        */
// /*EX.:		T_REDIR_OUT: " >   " 			        */
// /*EX.:		T_APPEND :   " >>  " 		                  */
// /*EX.:		T_HEREDOC :  " <<  "		                  */
// typedef enum e_token_type
// {
// 	T_WORD,
// 	T_PIPE,
// 	T_REDIR_IN,
// 	T_REDIR_OUT,
// 	T_APPEND,
// 	T_HEREDOC
// }	t_token_type;

// /* Armazenamos todos os comandos recebidos na struct abaixo em lista        */
// typedef struct s_token
// { 
// 	char		*value;
// 	t_token_type	type;
// 	s_token		*next;	
// }	t_token;


// /* ************************************************************************** */


// typedef enum e_state
// {
// 	STATE_GENERAL,
// 	STATE_IN_SQUOTE,
// 	STATE_IN_DQOTE
// }	t_state;


int	main(void);
/* lexer.c --------------------------------*/
t_token	*lexer(char *str);
int	get_token_type_and_len(t_token_type *node_type, char *str);

void	free_split(char **array);

#endif