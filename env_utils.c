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

#include "minishell.h"

t_env	*init_env(void)
{
	t_env	*envm;

	envm = (t_env *)malloc(sizeof(t_env));
	envm->cp_env = NULL;
	envm->cp_path = NULL;
	return (envm);
}

char	**copy_env(char **env)
{
	char	**envm;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (env[i++])
		len++;
	envm = (char **)malloc(sizeof(char *) * (len + 2));
	if (!envm)
		return (NULL);
	i = 0;
	while (env[i])
	{
		envm[i] = ft_strdup(env[i]);
		i++;
	}
	envm[i] = NULL;
	return (envm);
}
