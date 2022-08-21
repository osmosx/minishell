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

void	ft_blanc(int sig)
{
	(void)sig;
}

void	error(char *arg, int i, t_cmd *cmd, t_env *envm)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	else if (i == 2)
	{
		printf("minishell: %s: is a directory\n", arg);
		free_exit(cmd, envm);
		exit(126);
	}
	free_exit(cmd, envm);
	exit (127);
}

void	init_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		pipe(cmd->fd);
		cmd = cmd->next;
	}
}

int	open_file(char *name, int i, int quit)
{
	int		file;
	char	*err;

	file = 0;
	if (i == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(name, O_RDONLY, 0777);
	if (file == -1)
	{
		err = ft_strjoin("minishell: ", name);
		perror(err);
		free(err);
		g_error = 1;
		if (quit == 0)
			exit(1);
	}
	return (file);
}

int	find_path_env(t_env *envm)
{
	int	i;

	i = 0;
	while (envm->cp_env[i] && ft_strnstr(envm->cp_env[i], "PATH", 4) == 0)
		i++;
	return (i);
}
