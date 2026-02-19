/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:13:17 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/19 16:05:35 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


/* ************************************************************************** */
/*  		     TOKEN PART - ENUM AND LIST	        	        */
/* ************************************************************************** */
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
	char			*value;
	t_token_type	type;
}	t_token;


/* ************************************************************************** */


typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_SQUOTE,
	STATE_IN_DQOTE
}	t_state;

#endif