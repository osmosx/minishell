/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:51:15 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:51:16 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*home_path(t_env *envm, char *str)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envm->cp_env[i])
	{
		if (!ft_strncmp(envm->cp_env[i], str, ft_strlen(str)))
		{
			path = ft_strdup(envm->cp_env[i] + ft_strlen(str));
			break ;
		}
		i++;
	}
	if (path == NULL)
	{
		printf("cd: HOME not set\n");
		g_error = 1;
	}
	return (path);
}

static void	get_cwd_new_path(t_env *envm, char *str)
{
	char	c[PATH_MAX];

	getcwd(c, sizeof(c));
	new_path(str, c, envm);
}

static void	print_error(char *path)
{
	write(2, "cd: ", 4);
	perror(path);
	g_error = 1;
}

int	m_cd(t_env *envm, char *path)
{
	int		i;

	if (path)
	{
		i = chdir(path);
		get_cwd_new_path(envm, "OLDPWD=");
		if (i == 0)
			get_cwd_new_path(envm, "PWD=");
		else if (ft_strcmp(path, "~") == 0)
		{
			chdir(home_path(envm, "HOME="));
			get_cwd_new_path(envm, "PWD=");
		}
		else
			print_error(path);
	}
	if (!path && home_path(envm, "HOME="))
	{
		chdir(home_path(envm, "HOME="));
		get_cwd_new_path(envm, "PWD=");
	}
	else
		return (g_error);
	return (0);
}
