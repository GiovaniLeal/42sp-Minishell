/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:06:45 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/08 13:50:44 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expand.c -----------------------------------
void	expand_ast(t_ast *node, t_shell *shell);
void	expand_command(char **array, t_shell *shell);
char *expand_tokens(char *str, t_shell *shell);

//expand_utils.c -----------------------------------
char    *get_key(char *str, int *index);
char    *handle_dollar(char *res, char *str, int *index, t_shell *shell);
char    *append_char(char *res, char add);
int     check_quote(char c);