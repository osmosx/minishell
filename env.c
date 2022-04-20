#include "minishell.h"

void	m_env(t_env *envm)
{
	int	i;

	i = 0;
	while (envm->cp_env[i])
	{
		printf("%s\n", envm->cp_env[i]);
		i++;
	}
}
