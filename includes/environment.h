/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:30:02 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/07 20:30:02 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

// /* ************************************************************************** */
// /* 	                      STRUCTS 		        */
// /*       T_ENV - Struct of environment (envp)                                 */
// /*       T_SHELL - Contains list of environment end last exit status          */
// /* ************************************************************************** */
// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

// typedef struct s_shell
// {
// 	t_env	*lst_env;
// 	t_ast	*root;
// 	int		last_exit;
// 	int		exit_flag;
// }	t_shell;



/* ************************************************************************** */
/*          Function declarations and their respective .c files.              */
/* ************************************************************************** */

// ------------------------------------------------ environment_utils.c 
int		env_size(t_env *lst_env);
char	*str_join_three(char *key, char c, char *value);
void	free_env_array(char **env);
char	**env_to_array(t_env *env);
char	*get_environment(t_env *env, char *key);

// ------------------------------------------------------ *environment.c
void	add_environment(t_env **lst, t_env *node);
t_env	*create_environment(char *str);
t_env	*add_env(char **envp);
void	free_env_list(t_env *env_lst);

#endif