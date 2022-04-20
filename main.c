#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_env	*envm;
	char	*cmd;

	(void)argv;
	(void)argc;
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
		free(cmd);
	}
}
