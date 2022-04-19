#include "minishell.h"

int	g_status;

void	ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void)argv;
	(void)envp;
	(void)argc;
	g_status = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		cmd = readline(BEGIN(49, 31)"hellshell$> "CLOSE);
		add_history(cmd);
		free(cmd);
	}
}
