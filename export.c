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

static void	export_sort(char **buf)
{
	int		i;
	int		j;
	int		flag;
	char	*tmp;

	i = tablen(buf) - 1;
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

char	**export_nocmd(t_env *envm)
{
	int		i;
	char	**buf;

	i = 0;
	buf = con_twotab(envm->cp_env, envm->export);
	if (!buf)
		return (NULL);
	export_sort(buf);
	while (buf[i])
		printf("declare -x %s\n", buf[i++]);
	free(buf);
	return (envm->cp_env);
}

static int	find_cmd_env(char **env, char *arg)
{
	int		i;
	int		len;

	len = ft_strlen(arg);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0
			&& ((env[i][len] == '=') || (env[i][len] == '\0')))
			break ;
		else
			i++;
	}
	if (env[i] == NULL)
		return (-1);
	return (i);
}

static void	new_value_str(char **tab, char *new_str, int i)
{
	free(tab[i]);
	tab[i] = new_str;
}

static char	**del_line(char **arr, int j)
{
	int		i;
	int		k;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i));
	if (!new_arr)
		return (NULL);
	i = 0;
	k = 0;
	while (arr[i])
	{
		if (i != j)
			new_arr[k++] = ft_strdup(arr[i]);
		i++;
//		if (!new_arr[k - 1])
//			return (ft_free(new_arr));
	}
	new_arr[k] = NULL;
//	ft_free(arr);
	return (new_arr);
}

static t_env	*export_valid_arg(t_env *envm, char *cmd)
{
	int	str;

	if (ft_strchr(cmd, '=') == NULL)
	{
		if (find_cmd_env(envm->cp_env, cmd) == -1)
			if ((find_cmd_env(envm->export, cmd) == -1))
				envm->export = add_line(envm->export, cmd);
	}
	else
	{
		str = find_cmd_env(envm->cp_env, cmd);
		if (str == -1)
		{
			str = find_cmd_env(envm->export, cmd);
			envm->cp_env = add_line(envm->cp_env, cmd);
			if (!envm->cp_env)
				return (NULL);
			if (str)
				del_line(envm->export, str);
		}
		else
			new_value_str(envm->cp_env, cmd, str);
	}
	return (envm);
}

void	m_export(t_env *envm, char **cmd2)
{
	int	i;

	i = 1;
	if (cmd2[1] == NULL)
		export_nocmd(envm);
	while (cmd2[i])
	{
		if (check_export_arg(cmd2[i]) != 0)
		{
			i++;
			continue ;
		}
		export_valid_arg(envm, cmd2[i]);
		i++;
	}
}
