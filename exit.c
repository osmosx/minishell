#include "minishell.h"

static void	all_free(t_env *envm)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envm->cp_env[i])
	{
		free(envm->cp_env[i]);
		i++;
	}
	free(envm->cp_env);
	while (envm->cp_path[j])
	{
		free(envm->cp_path[j]);
		j++;
	}
	free(envm->cp_path);
	free(envm);
}

void	m_exit(t_env *envm)
{
	all_free(envm);
	printf("exit\n");
	rl_clear_history();
	exit(0);
}
