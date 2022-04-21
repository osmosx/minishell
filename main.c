#include "minishell.h"
#include <stdio.h>
#include <string.h>

int	g_status;

static void	test(t_env	*envm, char *cmd)
{
	if (ft_strcmp("env", cmd))
		m_env(envm);
	if (ft_strcmp("pwd", cmd))
		m_pwd();
//	if (ft_strcmp("echo", cmd))
//		m_echo(envm);
}


int	main(int argc, char **argv, char **envp)
{
	t_env	*envm;
	char	*cmd;

	(void)argc;
	(void)argv;
	g_status = 0;
	envm = init_env();
	envm->cp_path = ft_split(getenv("PATH"), ':');
	envm->cp_env = copy_env(envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		cmd = readline(BEGIN(49, 31)"hellshell$> "CLOSE);
		add_history(cmd);
		test(envm, cmd);
		printf("%s", cmd + 5);
	}
}
