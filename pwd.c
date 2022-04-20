#include "minishell.h"

int	m_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
