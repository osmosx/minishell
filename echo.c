#include "minishell.h"

void	m_echo(char **cmd2)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	if (ft_strcmp("-n", cmd2[1]))
		flag = 1;
	if (flag == 0)
	{
		i = 1;
		while (cmd2[i])
		{
			printf("%s", cmd2[i]);
			if (cmd2[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	if (flag == 1)
	{
		i = 1;
		j = 0;
		while (cmd2[j])
		{
			if (ft_strcmp("-n", cmd2[j]))
				i++;
			j++;
		}
		while (cmd2[i])
		{
			printf("%s", cmd2[i]);
			if (cmd2[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
}
