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

static int	check_exit_arg(char *cmd)
{
	int			i;
	long long	exit_code;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] && (cmd[i] == '+' || cmd[i] == '-'))
		i++;
	if (ft_isdigit(cmd[i]) == 0 || ft_isllong(cmd) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd);
		g_error = 255;
		return (g_error);
	}
	exit_code = ft_atoll(cmd);
	g_error = exit_code % 256;
	return (g_error);
}

int	m_exit(char **cmd, t_cmd *cmd_t, t_env *envm)
{
	int	i;

	i = 0;

	if (cmd[1] && !cmd[2])
	{
		i = check_exit_arg(cmd[1]);
	}
	if (cmd[1] && cmd[2] && i != 255)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_error = 1;
		return (g_error);
	}
	else
		g_error = 0;
	printf("exit\n");
	ft_free_cmd_list(&cmd_t);
	all_free(envm);
	exit(g_error);
}
