/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:25 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:27 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_check(char *arg)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i])
		{
			if (arg[i] == 'n')
				flag = 1;
			if (arg[i] != 'n')
			{
				flag = 0;
				break ;
			}
			i++;
		}
	}
	return (flag);
}

static void	echo_print_base(char **cmd2)
{
	int	i;

	i = 1;
	while (cmd2[i])
	{
		printf("%s", cmd2[i]);
		if (cmd2[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

static void	echo_print_flag(char **cmd2)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	while (cmd2[j])
	{
		if (echo_check(cmd2[j]))
			i++;
		j++;
	}
	while (cmd2[i])
	{
		printf("%s", cmd2[i]);
		if (cmd2[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	m_echo(char **cmd2)
{
	int	flag;

	flag = echo_check(cmd2[1]);
	if (flag == 0)
		echo_print_base(cmd2);
	if (flag == 1)
		echo_print_flag(cmd2);
	return (0);
}
