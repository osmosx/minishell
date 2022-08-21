/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:51:19 by keaton            #+#    #+#             */
/*   Updated: 2022/08/15 01:06:49 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stop_heredoc(int signal)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(130);
}

//Читает хердок в пайп до совпадения
void	heredoc(char *limiter, int *fd, t_cmd *cmd, t_env *env)
{
	char	*line;

	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	free_exit(cmd, env);
	exit(EXIT_SUCCESS);
}

//создаёт хердок в новом потоке и привязывает его к чтению.
//Если процесс прерывается, ставит ошибку 130
int	redir_heredoc(char *limiter, int fd, t_cmd *cmd, t_env *env)
{
	int		new_fd[2];
	pid_t	pid;
	int		wstatus;

	signal(SIGINT, ft_blanc);
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd, cmd, env);
	wait(&wstatus);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_error = WEXITSTATUS(wstatus);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}

//проверяем файлы в команде и если есть хердоки, то создаём их
int	make_heredocs(t_cmd *cmd, t_env *env)
{
	t_file	*file;

	file = NULL;
	if (cmd)
		file = cmd->begin_redirs;
	while (file != NULL)
	{
		if (file->type == 5)
		{
			if (redir_heredoc(file->name, cmd->fd[0], cmd, env) == 1)
				return (1);
		}
		file = file->next;
	}
	return (0);
}
