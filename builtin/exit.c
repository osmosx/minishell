/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:41 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:42 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	all_free(t_env *envm)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envm->cp_env[i])
	{
		free(envm->cp_env[i]);
		i++;
	}
	free(envm->cp_env);
	while (envm->cp_path[j])
	{
		free(envm->cp_path[j]);
		j++;
	}
	free(envm->cp_path);
	free(envm);
}

void	m_exit(t_env *envm)
{
	all_free(envm);
	printf("exit\n");
	exit(0);
}
