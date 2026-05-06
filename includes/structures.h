/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:35:37 by giodos-s          #+#    #+#             */
/*   Updated: 2026/05/06 14:35:37 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/* ************************************************************************** */
//*         		   TOKEN STRUCTS	                      */
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
//*         		  PARSING STRUCTS   	                      */
/* T_AST = If the node is CMD use the argv and redirs                         */
/* T_REDIR = For redirections comand control                                  */
/* T_PARSING_TYPE = For control the type of node (PIPE OR CMD)                */
/* ************************************************************************** */

typedef enum e_parsing_type
{
	NODE_CMD,
	NODE_PIPE
}	t_parsing_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_parsing_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv;
	t_redir			*redirs;
}	t_ast;

/* ************************************************************************** */
//* 	          SHELL AND ENVIRONMENT STRUCTS 		        */
/*       T_ENV - Struct of environment (envp)                                 */
/*       T_SHELL - Contains list of environment end last exit status          */
/* ************************************************************************** */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*lst_env;
	t_ast	*root;
	int		last_exit;
	int		exit_flag;
}	t_shell;
#endif