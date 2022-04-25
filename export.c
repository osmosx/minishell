#include "minishell.h"

void	m_export(t_env	*envm)
{
	int		i;
	int		j;
	char	**buf;
	int		flag;

	i = 0;
	while (envm->cp_env[i])
		i++;
	buf = malloc(sizeof(char *) * (i));
	i = i - 1;
	while (i >= 0)
	{
		flag = 1;
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(envm->cp_env[j], envm->cp_env[j + 1]) > 0)
			{
				buf[0] = envm->cp_env[j];
				envm->cp_env[j] = envm->cp_env[j + 1];
				envm->cp_env[j + 1] = buf[0];
				flag = 0;
			}
			j++;
		}
		if (flag == 1)
			break ;
		i--;
	}
	i = 0;
	while (envm->cp_env[i])
		printf("%s\n", envm->cp_env[i++]);

//	while (envm->cp_env[i])
//	{
//		buf[j] = NULL;
//		i++;
//		j++;
//	}
//	j = 0;
//	while (buf[j])
//		printf("%s\n", buf[j++]);
}

