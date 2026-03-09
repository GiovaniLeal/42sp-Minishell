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

#ifndef ENVIROMENT_H
# define ENVIROMENT_H
# include "minishell.h"

/*Estrutura da lista de ambientes recebidos por envp*/
typedef struct s_env
{
	char	*key;
	char	*value;
	struct  s_env	*next;
}	t_env;
/* Essa estrutura é responsável por armazenar o status do ultimo comando */
typedef struct s_shell
{
	t_env	*lst_env;
	int	last_exit;
}	t_shell;

/*environment_utils.c ------------------------------------------------------*/
char	*str_join_three(char *key, char c, char *value);
void	free_env_array(char **env);
int	env_size(t_env *lst_env);
char	**env_to_array(t_env *env);
char	*get_environment(t_env *env, char *key);
void	free_env_list(t_env *env_lst);

/*environment.c ------------------------------------------------------*/
void	add_environment(t_env **lst, t_env *node);
t_env	*create_environment(char *str);
t_env	*add_env(char **envp);

#endif