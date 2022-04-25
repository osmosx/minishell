#include "minishell.h"

static int	ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


void	m_export(t_env	*envm)
{
	int		i;
	int		j;
	char	**buf;
	int		n;
	int		noSwap;

	j = 0;
	i = 0;
	while (envm->cp_env[i])
		i++;
	n = i;
	buf = malloc(sizeof(char *) * (i));
	i = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		noSwap = 1;
		for (int j = 0; j < i; j++)
		{
			if (ft_strcmp2(envm->cp_env[j], envm->cp_env[j + 1]) > 0)
			{
				buf[0] = envm->cp_env[j];
				envm->cp_env[j] = envm->cp_env[j + 1];
				envm->cp_env[j + 1] = buf[0];
				noSwap = 0;
			}
		}
		if (noSwap == 1)
			break ;
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

