/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:21:32 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/19 16:06:48 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>


char	*check_absolute_path(char *cmd);
char	*search_in_dir(char	**dirs, char *cmd);
void	free_split(char **array);
char	*find_in_path(char	*cmd);
int		exit_status(int status);
void	execute_child(char *path, char **argv, char **envp);
int		exec_simple(char **argv, char **envp);

#endif