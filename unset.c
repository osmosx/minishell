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
//Придумать алгоритм
	return (new_env);
}

int	m_unset(t_env *envm, char **cmd2)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	j = 0;
	flag = 0;
	while (cmd2[i])
	{
		if (check_unset_cmd(cmd2[i]) != 0)
		{
			i++;
			continue ;
		}
		cmd = ft_split(cmd2[i], '=');
		envm->cp_env = unset_remove(envm, cmd[0]);
		i++;
	}
}
