/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:01 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:04 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
	return (NULL);
}

int	check_export_arg(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalpha(cmd[i]) == 0 && cmd[i] != '_')
	{
		printf("export: '%s': not a valid identifier\n", cmd);
		return (1);
	}
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n", cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (*tab++)
		i++;
	return (i);
}
