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

t_env	*init_env(t_env *envm, char **envp)
{
	envm = (t_env *)malloc(sizeof(t_env));
	envm->cp_env = NULL;
	envm->cp_path = ft_split(getenv("PATH"), ':');
	if (!copy_env(envm, envp))
		return (NULL);
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
