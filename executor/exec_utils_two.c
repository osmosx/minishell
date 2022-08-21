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
		{
			if (fd[0])
				close(fd[0]);
			fd[0] = open_file(ptr->name, 2, quit);
		}
		else if (ptr->type == 4)
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = open_file(ptr->name, 1, quit);
		}
		else if (ptr->type == 6)
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = open_file(ptr->name, 0, quit);
		}
		else if (ptr->type == 5)
		{
//			fd[0] = cmd->fd[0];
			if (fd[0])
				close(fd[0]);
			write(1, "\n", 1);//почему-то чинит передачу хердока через пайп, но ставит лишний перенос без пайпа
//			printf("\n");//почему-то чинит передачу хердока через пайп, но ставит лишний перенос без пайпа
			dup2(cmd->fd[0], STDIN_FILENO);
			fd[0] = 0;
		}
		ptr = ptr->next;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
	{
		if (cmd->fd[0])
			close(cmd->fd[0]);
		cmd->fd[0] = fd[0];
//		printf("redir -> <%d\n", cmd->fd[0]);//___________________
		dup2(fd[0], STDIN_FILENO);
	}
	if (fd[1])
	{
		cmd->fd[1] = fd[1];
//		printf("redir -> >%d\n", cmd->fd[0]);//___________________
		dup2(fd[1], STDOUT_FILENO);
	}
	return (0);
}
