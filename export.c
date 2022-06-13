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
	int		j;
	char	**buf;

	i = 0;
	buf = con_twotab(envm->cp_env, envm->export);
	if (!buf)
		return (NULL);
	export_sort(buf);
	while (buf[i])
	{
		if (ft_strchr(buf[i], '='))
		{
			write(1, "declare -x ", 11);
			j = 0;
			write(1, &(buf[i][j++]), 1);
			while (buf[i][j - 1] != '=')
				ft_putchar_fd(buf[i][j++], 1);
			ft_putchar_fd('"', 1);
			if (buf[i][j])
				printf("%s\"\n", buf[i] + j);
			i++;
		}
		else
			printf("declare -x ,%s\n", buf[i++]);
	}
	free(buf);
	return (envm->cp_env);
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

static char	**del_line(char **arr, int pos)
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

static int	find_line_in_tab(char **env, char *arg)
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

static void	change_line_value(char **tab, char *new_str, int i)
{
	free(tab[i]);
	tab[i] = ft_strdup(new_str);
}

static t_env	*export_valid_arg(t_env *envm, char *new_arg)
{
	int	pos;

	if (!ft_strchr(new_arg, '='))
	{
		if (find_line_in_tab(envm->cp_env, new_arg) < 0)
			if (find_line_in_tab(envm->export, new_arg) < 0)
				envm->export = add_line(envm->export, new_arg);
	}
	else
	{
		pos = find_line_in_tab(envm->cp_env, new_arg);
		if (pos < 0)
		{
			envm->cp_env = add_line(envm->cp_env, new_arg);
			if (!envm->cp_env)
				return (NULL);
			pos = find_line_in_tab(envm->export, new_arg);
			if (pos >= 0)
				envm->export = del_line(envm->export, pos);
//				envm->export = unset_remove(envm, new_arg);
		}
		else
			change_line_value(envm->cp_env, new_arg, pos);
	}
	if (!envm->export)
		return (NULL);
	return (envm);
}

t_env	*m_export(t_env *envm, char **cmd2)
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
		if (!export_valid_arg(envm, cmd2[i]))
			return (NULL);
		i++;
	}
	return (envm);
}
