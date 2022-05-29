/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:51:15 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:51:16 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_path(char *s, char *c, t_env *envm)
{
	int		i;
	char	*string;

	i = 0;
	string = ft_strjoin(s, c);
	while (envm->cp_env[i])
	{
		if (!ft_strncmp(envm->cp_env[i], s, ft_strlen(s)))
		{
			free(envm->cp_env[i]);
			envm->cp_env[i] = string;
			break ;
		}
		i++;
	}
}

void	m_cd(t_env *envm, char *path)
{
	char	c[PATH_MAX];

	getcwd(c, sizeof(c));
	new_path("OLDPWD=", c, envm);
	if (chdir(path) == 0)
	{
		getcwd(c, sizeof(c));
		new_path("PWD=", c, envm);
	}
	else
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
}
