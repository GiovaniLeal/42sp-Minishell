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

/*Serve para separar os nós que são do tipo pipe dos do tipo comando */
typedef enum e_parsing_type
{
	NODE_CMD;
	NODE_PIPE;
} t_parsing_type;

/* struct de redirecionamento de comandos*/
typedef struct s_redir
{
	t_token_type	type;
	char	*file;
	struct s_redir	*next;
} t_redir;

/*Essa é a struct da arvore sintática de comandos, caso o nó seja do tipo
NODE_CMD utilizaremos o parametro argv e redirs */
typedef struct s_ast
{
	t_parsing_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
	char	**argv;
	t_redir	*redirs;
} t_ast;

#endif