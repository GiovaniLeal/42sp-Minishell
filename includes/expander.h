/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:06:45 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/22 17:52:10 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

// ---------------------------------------------------------- expand.c
void	expand_ast(t_ast *node, t_shell *shell);
void	expand_command(char **array, t_shell *shell);
void	expand_redirs(t_redir	*redirs, t_shell *shell);
char	*expand_tokens(char *str, t_shell *shell);

// -------------------------------------------------------- expand_utils.c
char	*get_key(char *str, int *index);
char	*handle_dollar(char *res, char *str, int *index, t_shell *shell);
char	*append_char(char *res, char add);
int		change_quote_status(int state, char c);
int		is_quote_to_remove(int prev_state, int new_state, char c);

#endif