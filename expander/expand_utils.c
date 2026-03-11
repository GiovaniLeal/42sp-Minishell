/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:45:41 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/11 19:30:10 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*get_key = */
char    *get_key(char *str, int *index)
{
    char *key;

    key = ft_strdup("");
    while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
    {
        key = append_char(key, str[*index]);
        index++;
    }
    return (key);
}

/*handle_dollar*/
char    *handle_dollar(char *res, char *str, int *index, t_shell *shell)
{
    char    *key;
    char    *path;

    if (str[*index + 1] == '?')
    {
        free(res);
        res = ft_itoa(shell->last_exit);
        return (res);
    }
    key = get_key(str, index);
    //path = get_environment(shell->lst_env, key);
    /*IMPLEMENTAR !!!!!!!!!!!!!!!!!!!!!!!!!*/
    return (path);
}

/*Concatena caractere a uma string*/
char    *append_char(char *res, char add)
{
    char  *final_str;

    final_str = ft_strjoin(res, add);//REFATORAR (str + c) - nao usar strjoin
    free(res);
    return (final_str);
}

/* Para checar se o caractere é aspas duplas ou simples*/
int check_quote(char c)
{
    if (c == '\'')
        return (STATE_IN_SQUOTE);
    if (c == '\"')
        return (STATE_IN_DQUOTE);
    return (GENERAL_STATE);
}
