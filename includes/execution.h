/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/24 15:47:27 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;


char	*check_absolute_path(char *cmd);
char	*search_in_dir(char	**dirs, char *cmd);
void	free_split(char **array);
char	*find_in_path(char	*cmd);
int		exit_status(int status);
void	execute_child(char *path, char **argv, char **envp);
int		exec_simple(char **argv, char **envp);

#endif