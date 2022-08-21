/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:02 by keaton            #+#    #+#             */
/*   Updated: 2022/08/15 02:27:57 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_init_tab(char ***cmd, int i, t_tkn **tkn_begin)
{
	int		n;
	t_tkn	*tkn;

	n = 0;
	tkn = *tkn_begin;
	*cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!*cmd)
		return (NULL);
	(*cmd)[i] = NULL;
	while (n < i)
	{
		if (tkn->type == 1)
		{
			((*cmd)[n]) = ft_strdup(tkn->value);
			if (!(*cmd)[n++])
				return (ft_free(*cmd));
		}
		if (tkn->next)
			tkn = tkn->next;
	}
	return (*cmd);
}

//функция для заполнения **cmd для отработки команды
char	**ft_list_to_tab(t_tkn	**tkn_begin, char ***cmd)
{
	int		i;
	t_tkn	*tkn;

	tkn = *tkn_begin;
	// if (tkn && tkn->type != 0)
	// 	i = 1;
	// else
		i = 0;
	while (tkn)// && tkn->next)
	{
		if (tkn->type == 1)
			i++;
		tkn = tkn->next;
	}
	*cmd = ft_init_tab(cmd, i, tkn_begin);
//	if (tkn && tkn->type == 0)
//		ft_tkn_del(tkn, tkn_begin);
	if (!*cmd)
	{
		ft_free_tkn_list(tkn_begin);
		return (NULL);
	}
	return (*cmd);
}

t_tkn	**ft_cmd_filler_two(t_tkn *tkn, t_tkn **tkn_begin, t_file **redir_begin,
	char **env)
{
	while (tkn && tkn->next)
	{
		if (ft_is_redir(tkn->type))
		{
			if (!ft_file_add_back(ft_file_init(ft_filename(tkn, tkn_begin),
						tkn->type), redir_begin))
				return (ft_free_tkn_list(tkn_begin));
			tkn = ft_tkn_del(tkn, tkn_begin);
		}
		else
			if (tkn->next)
				tkn = tkn->next;
	}
	if (tkn && ft_is_redir(tkn->type))
	{
		if (!ft_file_add_back(ft_file_init(ft_filename(tkn, tkn_begin),
					tkn->type), redir_begin))
			return (ft_free_tkn_list(tkn_begin));
		ft_tkn_del(tkn, tkn_begin);
	}
	if (*redir_begin)
		if (!ft_dequote_file_list(redir_begin, env))
			return (ft_free_tkn_list(tkn_begin));
	return (tkn_begin);
}

//функция должна наполнять токен команды (и токен редиректа)
// полноценным содержимым
t_cmd	*ft_cmd_filler(t_tkn **tkn_begin, char **env)
{
	t_tkn	*tkn;
	t_cmd	*cmdt;
	t_file	*redir_begin;
	char	**cmd;

	cmdt = NULL;
	cmd = NULL;
	redir_begin = NULL;
	tkn = *tkn_begin;
	ft_tkn_prev_setter(*tkn_begin);
	if (!ft_cmd_filler_two(tkn, tkn_begin, &redir_begin, env))
		return (NULL);
	if (!ft_dequote_tkn_list(tkn_begin, env))
		return ((t_cmd *)ft_free_file_list(&redir_begin));
	if (!ft_list_to_tab(tkn_begin, &cmd))
		return ((t_cmd *)ft_free_file_list(&redir_begin));
	cmdt = ft_cmd_init(redir_begin, cmd);
	if (!cmdt)
		return (NULL);
	return (cmdt);
}
