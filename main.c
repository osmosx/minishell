/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:01 by nenvoy            #+#    #+#             */
/*   Updated: 2022/07/11 13:50:46 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			m_cd(env, cmd2[1]);
		else
			return (1);
//		write(1, "builtins\n", 9);
	}
	if (i == 0)
		return (0);
//	free_exit(first, shell);
	exit(0);
}

void	ft_printtab(char **cmds)
{
	if (!cmds)
		printf("No cmds tab");
	else
		while (*cmds)
			printf("%s\n", *(cmds++));
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envm;
	t_cmd	*cmd_begin = NULL;
	char	*cmd;
	char	**cmd2;

	(void)argc;
	(void)argv;
	g_status = 0;
	envm = NULL;
	envm = init_env(envm, envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		cmd = readline("\001\033[31m\002hellshell$>\001\033[0m\002 ");
		add_history(cmd);
		if (!cmd)
			ctrl_d(cmd, envm);
		if (*cmd)
		{
			cmd2 = ft_line_tokenizer(cmd, &cmd_begin, envp);
//			builtins(envm, cmd_begin->cmd, cmd_begin);
			ft_exec(cmd_begin, envm);
			ft_free_cmd_list(&cmd_begin);
			// файловые списки, таблицы команд и список команд)
			ft_free(cmd2);//не нужно, будет выполняться в ft_free_cmd_list
		}
		free(cmd);
	}
}
