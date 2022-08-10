/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:01:01 by keaton            #+#    #+#             */
/*   Updated: 2022/07/31 23:11:37 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_blanc(int sig)
{
	(void)sig;
}

void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(130);
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
//		free_exit(cmd, envm);
		exit(126);
	}
//	free_exit(cmd, envm);
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
//	free_exit(cmd, env);
	exit(EXIT_SUCCESS);
}

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

int	check_heredoc(t_file *redir, int stdin_fd, t_cmd *cmd, t_env *env)
{
	while (redir)
	{
		if (redir->type == 5)
		{
			if (redir_heredoc(redir->name, stdin_fd, cmd, env) == 1)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

int	make_heredocs(t_cmd *cmd, t_env *env)
{
	t_file	*file;

	file = NULL;
	if (cmd)
		file = cmd->begin_redirs;
	while (file != NULL)
	{
		if (check_heredoc(file, cmd->fd[0], cmd, env) == 1)
			return (1);
		file = file->next;
	}
	return (0);
}

int	open_file(char *name, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(name, O_RDONLY, 0777);
	if (file == -1)
	{
		perror(name);
		g_error = 1;
		if (access(name, F_OK) == 0)
			printf("minishell: %s Is a directory\n", name);
		else
			printf("minishell: no such file or directory: %s\n", name);
		if (quit == 0)
			exit(1);
	}
	return (file);
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
			dup2(cmd->fd[0], STDIN_FILENO);
//			fd[0] = cmd->fd[0];
		ptr = ptr->next;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
	{
		cmd->fd[0] = fd[0];
		dup2(fd[0], STDIN_FILENO);
	}
	if (fd[1])
	{
		cmd->fd[1] = fd[1];
		dup2(fd[1], STDOUT_FILENO);
	}
	return (0);
}

void	free_fds(t_cmd *begin_cmd)
{
	while (begin_cmd)
	{
		close(begin_cmd->fd[0]);
		close(begin_cmd->fd[1]);
		begin_cmd = begin_cmd->next;
	}
}

int	find_path_env(t_env *envm)
{
	int	i;

	i = 0;
	while (envm->cp_env[i] && ft_strnstr(envm->cp_env[i] , "PATH", 4) == 0)
		i++;
	return (i);
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
//			ft_free_tab(paths);
			return (path);
		}
	}
	free(path);
//	ft_free_tab(paths);
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
