/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:31 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:32 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*shlvl_create(char *ptr)
{
	int		len;
	char	*shlvl;
	int		lvl;
	char	*num;

	lvl = ft_atoi(ptr);
	lvl++;
	num = ft_itoa(lvl);
	len = ft_numlen(lvl);
	shlvl = malloc(7 + len);
	ft_strlcpy(shlvl, "SHLVL=", 7);
	ft_strlcpy(shlvl + 6, num, len + 1);
	free (num);
	return (shlvl);
}

void	check_shlvl(t_env *envm)
{
	int		i;
	char	*ptr;
	char	*shlvl;

	i = 0;
	ptr = NULL;
	while (envm->cp_env[i])
	{
		if (!ft_strncmp(envm->cp_env[i], "SHLVL=", 6))
		{
			ptr = envm->cp_env[i] + 6;
			break ;
		}
		i++;
	}
	if (!ptr)
		envm->cp_env = add_line(envm->cp_env, "SHLVL=1");
	else
	{
		shlvl = shlvl_create(ptr);
		envm->cp_env = del_line(envm->cp_env, i);
		envm->cp_env = add_line(envm->cp_env, shlvl);
		free(shlvl);
	}
}

t_env	*init_env(t_env *envm, char **envp)
{
	envm = (t_env *)malloc(sizeof(t_env));
	envm->cp_env = NULL;
	envm->cp_path = ft_split(getenv("PATH"), ':');
	if (!copy_env(envm, envp))
		return (NULL);
	check_shlvl(envm);
	envm->export = (char **)malloc(sizeof (char *));
	if (!envm->export)
		return (NULL);
	*(envm->export) = 0;
	return (envm);
}

char	**copy_env(t_env *envm, char **env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (env[i++])
		len++;
	envm->cp_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envm->cp_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		envm->cp_env[i] = ft_strdup(env[i]);
		i++;
	}
	envm->cp_env[i] = NULL;
	return (envm->cp_env);
}
