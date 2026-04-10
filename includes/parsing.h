/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:34:51 by giodos-s          #+#    #+#             */
/*   Updated: 2026/02/21 19:34:51 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ************************************************************************** */
/*			PARSING ENUM AND STRUCT		        */
/* ************************************************************************** */
/*							        */
/*   Serve para separar os nós que são do tipo pipe dos do tipo comando       */
typedef enum e_parsing_type
{
	NODE_CMD,
	NODE_PIPE
}	t_parsing_type;

/* 		struct de redirecionamento de comandos                    */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

/*Essa é a struct da arvore sintática de comandos, caso o nó seja do tipo
NODE_CMD utilizaremos o parametro argv e redirs */
typedef struct s_ast
{
	t_parsing_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv;
	t_redir			*redirs;
}	t_ast;
/*                                                                            */
/* ************************************************************************** */

/* parsing.c -----------------------------------------------------------------*/
t_ast	*parser(t_token *token_list);
t_ast	*parse_pipeline(t_token **current_token);
t_ast	*parse_command(t_token **current_token);
int		add_arg(t_ast *cmd_node, char *token_value);
int		add_redir(t_ast *cmd, t_token_type type, char *file);

/* parsing_utils.c ----------------------------------------------------------*/
int		is_redir(t_token_type type);
int		add_new_arg(t_ast *cmd_node, char *value);
t_ast	*new_pipe_node(t_ast *left, t_ast *right);
t_ast	*new_cmd_node(void);

/* parsing_free.c ------------------------------------------------------------*/
void	free_ast(t_ast *node);
void	free_redirs(t_redir *redir);
void	free_argv(char **argv);

/* parsing_tester.c ----------------------------------------------------------*/
void	print_ast_tree(t_ast *node, int depth);
#endif