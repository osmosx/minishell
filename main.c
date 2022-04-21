#include "minishell.h"

int	g_status;

static void	test(t_env	*env, char *cmd, char **cmd2)
{
	if (ft_strcmp("env", cmd))
		m_env(env);
	if (ft_strcmp("pwd", cmd))
		m_pwd();
	if (ft_strcmp("echo", cmd2[0]))
		m_echo(cmd2);
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
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		cmd = readline(BEGIN(49, 31)"hellshell$> "CLOSE);
		add_history(cmd);
		cmd2 = ft_split(cmd, ' ');
		test(envm, cmd, cmd2);
	}
}
