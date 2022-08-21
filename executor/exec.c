/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:01:01 by keaton            #+#    #+#             */
/*   Updated: 2022/08/15 03:54:48 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process(t_cmd *cmd, t_cmd *begin_cmd, t_env *env)
{
	signal(SIGINT, ft_blanc);
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("pid error");
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd->prev)
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		if (cmd->next)
			dup2(cmd->fd[1], STDOUT_FILENO);
		check_redirection(cmd, 0);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		free_fds(begin_cmd);
		if (cmd->cmd && builtins(cmd->cmd, begin_cmd, env, 1) == 1)
			executor(cmd->cmd, begin_cmd, env);//заменить на из пайпекса
	}
	if (cmd->prev)
		close(cmd->prev->fd[0]);
	close(cmd->fd[1]);
}

int	check_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0
		||ft_strcmp(arg[0], "cd") == 0
		||ft_strcmp(arg[0], "pwd") == 0
		||ft_strcmp(arg[0], "export") == 0
		||ft_strcmp(arg[0], "unset") == 0
		||ft_strcmp(arg[0], "env") == 0
		||ft_strcmp(arg[0], "exit") == 0)
		return (0);
	else
		return (1);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, 0);
	close(saved_stdin);
	dup2(saved_stdout, 1);
	close(saved_stdout);
}

int	ft_builtin(t_cmd *cmd, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (cmd && cmd->next == NULL && cmd->cmd[0] != NULL)
	{
		if (cmd->cmd && check_builtins(cmd->cmd) == 1)
			return (0);
		if (check_redirection(cmd, 1) == 1)
			return (1);
		if (builtins(cmd->cmd, cmd, env, 0) == 0)
		{
			restore_fd(saved_stdin, saved_stdout);
			return (1);
		}
	}
	return (0);
}

void	ft_exec(t_cmd *cmd, t_env *env)
{
	t_cmd	*begin_cmd;
	int		status;

	status = 0;
	begin_cmd = cmd;
	init_pipe(begin_cmd);
	if (make_heredocs(cmd, env) == 1 || ft_builtin(cmd, env) == 1)
	{
//		perror("file");
		return ;
	}
	if (cmd && cmd->cmd)
	{
		while (cmd)
		{
			process(cmd, begin_cmd, env);
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				g_error = WEXITSTATUS(status);
			cmd = cmd->next;
		}
	}
	signal(SIGINT, handler);
}
