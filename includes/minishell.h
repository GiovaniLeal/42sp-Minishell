/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:28:40 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/21 19:28:40 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                             STANDART LIBRARIES                             */
/* ************************************************************************** */
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>



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
/*         		      STRUCTS   	                      */
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
/* 	                      STRUCTS 		        */
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

/* ************************************************************************** */
/*                          DEFINED HEADERS                                   */
/* ************************************************************************** */
# include "libft.h"
# include "ft_printf.h"
# include "environment.h"
# include "tokens.h"
# include "parsing.h"
# include "execution.h"
# include "environment.h"
# include "expander.h"
# include "signals.h"
# include "builtins.h"


/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

// ------------------------------------------------- utils.c
void	free_split(char **array);
int		error_msg(char *cmd, char *detail, char *msg, int error_nbr);
long	ft_atol_safe(const char *nptr, int *error);

// FUNCAO TESTES!
void	clear_all(t_ast *node, t_shell *shell);
#endif
