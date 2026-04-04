/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:34:03 by anunes-o          #+#    #+#             */
/*   Updated: 2026/04/04 16:45:33 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* vai apenas gerar um nome único para cada arquivo temporário do heredoc*/
static char	*generate_heredoc_name(void)
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

/* vai popular o arquivo temporário linha por linha, até o delimiter ser 
encontrado, pra depois heredoc poder reabrir esse arquivo em modo leitura
*/
static int	write_line(int fd, char *line, char *filename)
{
	if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
	{
		perror("write");
		return (close_fd(fd, line, filename));
	}
	free(line);
	return (0);
}

static	int	heredoc_loop(int fd, char *delimiter, char *filename)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (get_signal() == 130)
		{
			reset_signal();
			return (close_fd(fd, line, filename));
		}
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write_line(fd, line, delimiter) < 0)
			return (-1);
	}
	return (0);
}

/* 
*/
int	heredoc(char *delimiter)
{
	int		fd;
	char	*filename;

	filename = generate_heredoc_name();
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (heredoc_loop(fd, delimiter, filename) < 0)
		return (-1);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd);
}

