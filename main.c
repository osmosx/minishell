/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:01 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:04 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	test(t_env	*env, char **cmd2)
{
	if (ft_strcmp("env", cmd2[0]) == 0)
		m_env(env);
	if (ft_strcmp("pwd", cmd2[0]) == 0)
		m_pwd();
	if (ft_strcmp("echo", cmd2[0]) == 0)
		m_echo(cmd2);
	if (ft_strcmp("exit", cmd2[0]) == 0)
		m_exit(env);
	if (ft_strcmp("export", cmd2[0]) == 0)
		m_export(env, cmd2);
	if (ft_strcmp("unset", cmd2[0]) == 0)
		m_unset(env, cmd2);
	if (ft_strcmp("cd", cmd2[0]) == 0)
		m_cd(env, cmd2[1]);
	else
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envm;
	char	*cmd;
	char	**cmd2;

	(void)argc;
	(void)argv;
	g_status = 0;
	envm = init_env();
	envm->cp_path = ft_split(getenv("PATH"), ':');
	envm->cp_env = copy_env(envp);
	envm->export = copy_env(envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		cmd = readline("\001\033[31m\002hellshell$>\001\033[0m\002 ");
		add_history(cmd);
		cmd2 = ft_split(cmd, ' ');
		test(envm, cmd2);
		ft_free(cmd2);
		free(cmd);
	}
}
