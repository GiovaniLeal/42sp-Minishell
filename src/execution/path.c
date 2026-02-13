/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anunes-o <anunes-o@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:23:11 by anunes-o          #+#    #+#             */
/*   Updated: 2026/02/13 14:46:37 by anunes-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Quando o execve precisar buscar o executável path vai achar o caminho
e o diretório em que o comando especifico se encontra */
/* vai localizar o comando antes de executa-lo*/
char	*find_in_path(char	*cmd)
{
	char	*path;
	char	**dirs;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	result = search_in_dir(dirs, cmd);
	return (result);
}

/* Se o comando ja tem uma barra (/) ele é um caminho absoluto ou relativo */
char	*check_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

/* vai procurar o comando dentro dos diretórios e testar sua execução */
char	*search_in_dir(char	**dirs, char *cmd)
{
	char	*temp;
	char	*path_candidate;
	int		i;

	i = 0;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		path_candidate = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_candidate, X_OK) == 0)
			return (path_candidate);
		free(path_candidate);
		i++;
	}
	free_split(dirs);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	int		i;

	if (argc < 2)
	{
		printf("Usage: %s <command> [args...]\n", argv[1]);
		return (1);
	}
	path = find_in_path(argv[1]);
	if (!path)
	{
		perror("Command not found");
		return (1);
	}
	printf("Executing %s ...\n", argv[1]);
	execve(path, &argv[1], envp);
	perror("execve failed");
	return (1);
}
