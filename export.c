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

void	m_export(t_env	*envm)
{
	int		i;
	int		j;
	int		len;
	char	**buf;

	len = 0;
	j = 0;
	i = 0;
	while (envm->cp_env[len])
		len++;
	buf = malloc(sizeof(char *) * (len));
	while (envm->cp_env[i])
		buf[j++] = envm->cp_env[i++];
	buf = export_sort(buf, len);
	i = 0;
	while (buf[i])
		printf("declare -x %s\n", buf[i++]);
}
