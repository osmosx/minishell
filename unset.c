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

static char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
	return (NULL);
}

static int	check_unset_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalpha(cmd[i]) == 0 && cmd[i] != '_')
	{
		printf("unset: '%s': not a valid identifier\n", cmd);
		return (1);
	}
	i++;
	while (cmd[i])
	{
		if ((ft_isalnum(cmd[i]) == 0 && cmd[i] != '_') || cmd[i] == '=')
		{
			printf("unset: '%s': not a valid identifier\n", cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

static char	**unset_remove(t_env *envm, char *cmd)
{
	char	**new_env;
	int		i;
	int		len;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (envm->cp_env[i])
		if (ft_strncmp(envm->cp_env[i++], cmd, ft_strlen(cmd)))
			len++;
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envm->cp_env[i])
	{
		if (ft_strncmp(envm->cp_env[i++], cmd, ft_strlen(cmd)))
			new_env[i - j - 1] = ft_strdup(envm->cp_env[i - 1]);
		else
			j++;
	}
	new_env[i - j] = NULL;
	ft_free(envm->cp_env);
	return (new_env);
}

void	m_unset(t_env *envm, char **cmd2)
{
	int		i;

	i = 0;
	while (cmd2[i])
	{
		if (check_unset_cmd(cmd2[i]) != 0)
		{
			i++;
			continue ;
		}
		envm->cp_env = unset_remove(envm, cmd2[i]);
		i++;
	}
}
