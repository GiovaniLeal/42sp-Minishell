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
// *                          Path = /SRC/PARSING                             */
/*         - Function declarations and their respective .c files -            */
/* ************************************************************************** */
// * parsing.c
t_ast	*parser(t_token *token_list);
t_ast	*parse_pipeline(t_token **current_token);
t_ast	*parse_command(t_token **current_token);
int		add_arg(t_ast *cmd_node, char *token_value);
int		add_redir(t_ast *cmd, t_token_type type, char *file);

// * parsing_utils.c
int		is_redir(t_token_type type);
int		add_new_arg(t_ast *cmd_node, char *value);
t_ast	*new_pipe_node(t_ast *left, t_ast *right);
t_ast	*new_cmd_node(void);
int		handle_token(t_ast *command, t_token **current_token);

// * parsing_free.c
void	free_ast(t_ast *node);
void	free_redirs(t_redir *redir);
void	free_argv(char **argv);
#endif