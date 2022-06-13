/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:50:01 by nenvoy            #+#    #+#             */
/*   Updated: 2022/06/13 15:50:04 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_line_value(char **tab, char *new_str, int i)
{
	free(tab[i]);
	tab[i] = ft_strdup(new_str);
}

int	find_line_in_tab(char **env, char *arg)
{
	int		i;
	int		len;

	len = 0;
	while (arg[len] != '\0' && arg[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, len) && ((env[i][len] == '=')
			|| (env[i][len] == '\0')))
			return (i);
		i++;
	}
	return (-1);
}

char	**del_line(char **arr, int pos)
{
	int		i;
	int		k;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * i);
	if (!new_arr)
		return (NULL);
	i = 0;
	k = 0;
	while (arr[i])
	{
		if (i++ != pos)
		{
			new_arr[k] = ft_strdup(arr[i - 1]);
			if (!new_arr[k++])
				return (ft_free(new_arr));
		}
	}
	new_arr[k] = NULL;
	ft_free(arr);
	return (new_arr);
}

char	**add_line(char **arr, char *new_line)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i++])
			return (ft_free(new_arr));
	}
	new_arr[i] = ft_strdup(new_line);
	if (!new_arr[i++])
		return (ft_free(new_arr));
	new_arr[i] = NULL;
	ft_free(arr);
	return (new_arr);
}

char	**con_twotab(char **tab, char **tab2)
{
	int		i;
	int		j;
	int		len;
	char	**buf;

	len = tablen(tab) + tablen(tab2);
	buf = malloc(sizeof(char *) * (len + 1));
	if (!buf)
		return (0);
	i = 0;
	j = 0;
	while (tab && tab[j])
		buf[i++] = tab[j++];
	j = 0;
	while (tab2 && tab2[j])
		buf[i++] = tab2[j++];
	buf[i] = NULL;
	return (buf);
}
