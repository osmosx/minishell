/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:47 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:48 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**export_sort(char **buf, int i)
{
	int		j;
	int		flag;
	char	*tmp;

	i = i - 1;
	while (i >= 0)
	{
		flag = 1;
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(buf[j], buf[j + 1]) > 0)
			{
				tmp = buf[j];
				buf[j] = buf[j + 1];
				buf[j + 1] = tmp;
				flag = 0;
			}
			j++;
		}
		if (flag == 1)
			break ;
		i--;
	}
	return (buf);
}

void	export_nocmd(t_env	*envm)
{
	int		i;
	int		j;
	int		len;
	char	**buf;

	len = 0;
	j = 0;
	i = 0;
	while (envm->export[len])
		len++;
	buf = malloc(sizeof(char *) * (len));
	while (envm->export[i])
		buf[j++] = envm->export[i++];
	buf = export_sort(buf, len);
	i = 0;
	while (buf[i])
		printf("declare -x %s\n", buf[i++]);
}

void	m_export(t_env	*envm, char **cmd2)
{
	int		i;
	char	**str;

	i = 0;
	while (cmd2[i])
	{
		if (check_export_arg(cmd2[i]) != 0)
		{
			i++;
			continue ;
		}
		str = ft_split(cmd2[i], '=');
		ft_free_tab(str);
		i++;
	}
	if (cmd2[1] == NULL)
		export_nocmd(envm);
}
