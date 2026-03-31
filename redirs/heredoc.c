/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:34:03 by anunes-o          #+#    #+#             */
/*   Updated: 2026/03/31 16:19:03 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* vai comparar se a situação contem ou não o heredoc e também se ele esta 
ou não dentro de pipes, se certificando também a execução do heredoc na 
sequência certa, também atribui os valores na struct de t_redir
     cat << EOF
	(fd)    (delimitador)
*/
int	apply_heredocs(t_ast *node)
{
	t_redir	*tmp;
	int		fd;

	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
	{
		if (apply_heredocs(node->left) < 0)
			return (-1);
		if (apply_heredocs(node->right) < 0)
			return (-1);
		return (0);
	}
	else
	{
		tmp = node->redirs;
		while (tmp)
		{
			if (tmp->type == T_HEREDOC)
			{
				fd = heredoc(tmp->file);
				if (fd < 0)
					return (-1);
				tmp->heredoc_fd = fd;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

/* vai apenas gerar um nome único para cada arquivo temporário do heredoc*/
char	*generate_heredoc_name(void)
{
	static int	index;
	char		*value;
	char		*name;

	value = ft_itoa(index);
	name = ft_strjoin("/tmp/heredoc_", value);
	free(value);
	index++;
	return (name);
}

/* 
*/
int	heredoc(char *delimiter)
{
	int		fd;
	char	*line;
	char	*filename;
	ssize_t	ret;

	line = NULL;
	filename = generate_heredoc_name();
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		if (get_signal() == 130)
		{
			if (line)
				free(line);
			close(fd);
			unlink(filename);
			reset_signal();
			return (-1);
		}
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ret = write(fd, line, ft_strlen(line));
		ret = write(fd, "\n", 1);
		if (line)
			free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd);
}
