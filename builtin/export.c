/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:47 by nenvoy            #+#    #+#             */
/*   Updated: 2022/08/21 03:00:06 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	print_export(char **buf)
{
	int		i;
	int		j;

	i = 0;
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
				printf("%s", buf[i] + j);
			printf("\"\n");
			i++;
		}
		else
			printf("declare -x %s\n", buf[i++]);
	}
}

static char	**export_nocmd(t_env *envm)
{
	char	**buf;

	buf = con_twotab(envm->cp_env, envm->export);
	if (!buf)
		return (NULL);
	export_sort(buf);
	print_export(buf);
	free(buf);
	return (envm->cp_env);
}

static char	**export_valid_arg(t_env *envm, char *new_arg)
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
		}
		else
			change_line_value(envm->cp_env, new_arg, pos);
	}
	return (envm->export);
}

int	m_export(t_env *envm, char **cmd2)
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
			return (0);
		i++;
	}
	return (0);
}
