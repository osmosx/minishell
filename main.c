/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:01 by nenvoy            #+#    #+#             */
/*   Updated: 2022/08/07 23:04:08 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	builtins(char **cmd2, t_cmd *cmd, t_env	*env, int i)
{
	if (cmd2)
	{
		if (ft_strcmp("env", cmd2[0]) == 0)
			g_error = m_env(env);
		else if (ft_strcmp("pwd", cmd2[0]) == 0)
			g_error = m_pwd();
		else if (ft_strcmp("echo", cmd2[0]) == 0)
			g_error = m_echo(cmd2);
		else if (ft_strcmp("exit", cmd2[0]) == 0)
			g_error = m_exit(cmd2, cmd, env);
		else if (ft_strcmp("export", cmd2[0]) == 0)
			g_error = m_export(env, cmd2);
		else if (ft_strcmp("unset", cmd2[0]) == 0)
			g_error = m_unset(env, cmd2);
		else if (ft_strcmp("cd", cmd2[0]) == 0)
			g_error = m_cd(env, cmd2[1]);
		else
			return (1);
	}
	if (i == 0)
		return (0);
	free_exit(cmd, env);
	exit(0);
}

void	silly_func(int ac, char **av, t_env **envm, char **envp)
{
	(void)ac;
	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	*envm = init_env(*envm, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envm;
	t_cmd	*cmd_begin;
	char	*cmd;

	envm = NULL;
	cmd_begin = NULL;
	silly_func(argc, argv, &envm, envp);
	while (42)
	{
		cmd = readline("\001\033[31m\002hellshell$\001\033[0m\002 ");
		add_history(cmd);
		if (!cmd)
			ctrl_d(cmd, envm);
		if (*cmd && !ft_quotes_checker(cmd))
		{
			if (!ft_line_tokenizer(cmd, &cmd_begin, envm->cp_env))
			{
				free(cmd);
				continue ;
			}
			ft_exec(cmd_begin, envm);
			ft_free_cmd_list(&cmd_begin);
		}
		free(cmd);
	}
}
