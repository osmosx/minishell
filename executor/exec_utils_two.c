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

void	free_exit(t_cmd *cmd, t_env *envm)
{
	if (cmd)
		ft_free_cmd_list(&cmd);
	if (envm)
	{
		if (envm->cp_env)
			ft_free(envm->cp_env);
		if (envm->cp_path)
			ft_free(envm->cp_path);
		if (envm->export)
			ft_free(envm->export);
	}
}

int	ft(int fd, t_file *ptr, int quit, int n)
{
	if (fd)
		close(fd);
	fd = open_file(ptr->name, n, quit);
	return (fd);
}

int	ft2(int fd, t_cmd *cmd)
{
	if (fd)
		close(fd);
	dup2(cmd->fd[0], STDIN_FILENO);
	fd = 0;
	return (fd);
}

void	ft3(int fd, t_cmd *cmd, int i)
{
	if (i == 0)
		if (cmd->fd[i])
			close(cmd->fd[i]);
	cmd->fd[i] = fd;
	dup2(fd, i);
}

int	check_redirection(t_cmd *cmd, int quit)
{
	int		fd[2];
	t_file	*ptr;

	fd[0] = 0;
	fd[1] = 0;
	ptr = cmd->begin_redirs;
	while (ptr)
	{
		if (ptr->type == 3)
			fd[0] = ft(fd[0], ptr, quit, 2);
		else if (ptr->type == 4)
			fd[1] = ft(fd[1], ptr, quit, 1);
		else if (ptr->type == 6)
			fd[1] = ft(fd[1], ptr, quit, 0);
		else if (ptr->type == 5)
			fd[0] = ft2(fd[0], cmd);
		ptr = ptr->next;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		ft3(fd[0], cmd, 0);
	if (fd[1])
		ft3(fd[1], cmd, 1);
	return (0);
}
