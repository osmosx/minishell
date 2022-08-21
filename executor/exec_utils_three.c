/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:55:07 by keaton            #+#    #+#             */
/*   Updated: 2022/08/14 23:55:46 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_fds(t_cmd *begin_cmd)
{
	while (begin_cmd)
	{
		close(begin_cmd->fd[0]);
		close(begin_cmd->fd[1]);
		begin_cmd = begin_cmd->next;
	}
}

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*tabs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tabs = (char *)malloc(sizeof(*tabs) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (tabs == 0)
		return (NULL);
	while (s1[i])
	{
		tabs[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tabs[i] = s2[j];
		j++;
		i++;
	}
	tabs[i] = '\0';
	free(s1);
	return (tabs);
}

char	*find_path(char *cmd, t_cmd *cmdl, t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = find_path_env(env);
	if (env->cp_env[i] == NULL)
		error(cmd, 1, cmdl, env);
	paths = ft_split(env->cp_env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		if (path)
			free(path);
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free(paths);
			return (path);
		}
	}
	free(path);
	ft_free(paths);
	return (NULL);
}

void	executor(char **argv, t_cmd *cmd, t_env *env)
{
	char	*path;

	execve(argv[0], argv, env->cp_env);
	if (ft_strchr(argv[0], '/') != NULL)
	{
		if (access(argv[0], F_OK) == 0)
			error(argv[0], 2, cmd, env);
		error(argv[0], 1, cmd, env);
	}
	path = find_path(argv[0], cmd, env);
	if (path && (execve(path, argv, env->cp_env) == -1))
		error(argv[0], 0, cmd, env);
	error(argv[0], 0, cmd, env);
}
