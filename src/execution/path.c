/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:23:11 by anunes-o          #+#    #+#             */
/*   Updated: 2026/05/04 20:42:51 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if the command contains a '/' (absolute or relative path).
   If so, validates its existence and execution permissions.

   - If the file does not exist → exit(127)
   - If it exists but is not executable → exit(126)
   - Otherwise, returns a duplicated valid path

   Returns NULL if the command does not contain '/'
*/
char	*check_absolute_path(char *cmd, t_shell *shell)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			shell->last_exit = 127;
			return (NULL);
		}
		if (access(cmd, X_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			shell->last_exit = 126;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

/* Searches for the command in the given list of directories (PATH).

   - Iterates through each directory
   - Builds a full path candidate (dir + '/' + cmd)
   - Checks if the file is executable (X_OK)

   Returns:
   - A valid executable path if found
   - NULL if the command is not found in any directory

   Frees the dirs array before returning
*/
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
		{
			free_split(dirs);
			return (path_candidate);
		}
		free(path_candidate);
		i++;
	}
	free_split(dirs);
	return (NULL);
}

/* Resolves the full path of a command before execution.

   - First checks if the command is an absolute or relative path
   - Otherwise, retrieves the PATH environment variable
   - Splits PATH into directories
   - Searches for the executable in those directories

   Returns:
   - A valid executable path if found
   - NULL if the command cannot be resolved
*/
char	*find_in_path(char *cmd, t_shell * shell)
{
	char	*path;
	char	**dirs;
	char	*result;

	result = check_absolute_path(cmd, shell);
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

/* Handles execution of commands that include a '/' in their path
   (absolute or relative paths).

   - Checks if the path points to a directory
   - Verifies file existence (F_OK)
   - Verifies execution permission (X_OK)
   - Executes the command directly if all checks pass

   Exits with appropriate error codes on failure.
*/
int	handle_path_command(t_ast *node, t_shell *shell)
{
	struct stat	st;

	if (stat(node->argv[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: Is a directory\n", 2);
		shell->last_exit = 126;
	}
	else if (access(node->argv[0], F_OK) != 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		shell->last_exit = 127;
	}
	else if (access(node->argv[0], X_OK) != 0)
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		shell->last_exit = 126;
	}
	execute_child(node->argv[0], node->argv, shell->lst_env);
	return(shell->last_exit);
}


void	exit_status(t_ast *node, t_shell *shell, char *str_error, int exit_number)
{
	write(2, str_error, ft_strlen(str_error));
	shell->last_exit = exit_number;
	free_ast(node);
	free_env_list(shell->lst_env);
}

/* Handles the case where a command cannot be resolved via PATH.

   - Checks if the command exists in the current directory
   - If it exists but is not executable → returns permission error (126)
   - If it is a directory → treated as command not found (127)
   - Otherwise → command not found (127)

   This function always exits with the correct status code.
*/
void	handle_path_not_found(char *cmd)
{
	struct stat	st;

	// 1. Existe?
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd(" command not found\n", 2);
		//perror("minishell"); // imprime mensagem real (No such file, etc)
		exit(127);
	}

	// 2. É diretório?
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		write(2, "minishell: Is a directory\n", 26);
		exit(126);
	}
	else if (stat(cmd, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(" command not found\n", 2);
		exit (127);
	}

	// 3. Tem permissão de execução?
	if (access(cmd, X_OK) != 0)
	{
		perror("minishell"); // geralmente "Permission denied"
		exit(126);
	}
}
