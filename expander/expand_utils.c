/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:45:41 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/26 16:08:04 by giodos-s         ###   ########.fr       */
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
        (*index)++;
    }
    return (key);
}

/*handle_dollar*/
char *handle_dollar(char *res, char *str, int *index, t_shell *shell)
{
    char *key;
    char *value;

    (*index)++; // pula o '$'

    if (str[*index] == '?')
    {
        (*index)++;
        free(res);
        return (ft_itoa(shell->last_exit));
    }

    key = get_key(str, index);
    value = get_environment(shell->lst_env, key);

    free(key);

    if (!value)
        return (res); // variável inexistente = vazio (bash-like)

    return (ft_strjoin(res, value));
}

/*Concatena caractere a uma string*/
char *append_char(char *res, char add)
{
    char tmp[2];
    char *final_str;

    tmp[0] = add;
    tmp[1] = '\0';
    final_str = ft_strjoin(res, tmp);
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
    return (STATE_GENERAL);
}
