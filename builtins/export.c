/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:55:37 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/07 00:08:52 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_update(t_env *node, char *str)
{
	int		i;
	int		append;
	char	*new_value;
	char	*tmp;

	i = 0;
	append = 0;

	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			append = 1;
			break ;
		}
		i++;
	}
	if (!str[i])
		return ;
	i += append ? 2 : 1;
	new_value = ft_strdup(str + i);
	if (!new_value)
		return ;

	if (append && node->value)
	{
		tmp = ft_strjoin(node->value, new_value);
		free(node->value);
		free(new_value);
		node->value = tmp;
	}
	else
	{
		free(node->value);
		node->value = new_value;
	}
}

t_env	*find_in_lst(char *str, t_env *env)
{
	size_t	i;
	t_env	*temp_node;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	temp_node = env;
	while (temp_node)
	{
		if (ft_strncmp(temp_node->key, str, i) == 0
			&& temp_node->key[i] == '\0')
			return (temp_node);
		temp_node = temp_node->next;
	}
	return (NULL);
}

int	is_valid_arg(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);

	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exec_export(char **argv, t_shell *shell)
{
	int		i;
	t_env	*node;

	if (!argv[1])
		return (display_export(shell->lst_env));

	i = 1;
	while (argv[i])
	{
		if (!is_valid_arg(argv[i]))
		{
			ft_printf("export: `%s': not a valid identifier\n", argv[i]);
			i++;
			continue;
		}
		node = find_in_lst(argv[i], shell->lst_env);
		if (node)
			export_update(node, argv[i]);
		else
		{
			node = create_environment(argv[i]);
			if (!node)
				return (1);
			add_environment(&shell->lst_env, node);
		}
		i++;
	}
	return (0);
}

