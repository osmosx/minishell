/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:21:49 by keaton            #+#    #+#             */
/*   Updated: 2022/08/15 01:32:12 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_cmd(t_cmd	*tkn)
{
	if (tkn->cmd)
		ft_free(tkn->cmd);
	if (tkn->begin_redirs)
		ft_free_file_list(&tkn->begin_redirs);
	free(tkn);
}

//проверяет, передали ли начало и если да, то фришит строки и токены
t_cmd	**ft_free_cmd_list(t_cmd **begin_cmd)
{
	t_cmd	*active;
	t_cmd	*prev;

	if (!begin_cmd || !*begin_cmd)
		return (NULL);
	active = *begin_cmd;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_cmd(prev);
		prev = active;
	}
	ft_free_cmd(active);
	*begin_cmd = NULL;
	return (NULL);
}

//инициализирует команду с атрибутами, заполняет нужные значения и возвращает её
// адрес
t_cmd	*ft_cmd_init(t_file *begin_redirs, char **cmd)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = cmd;
	new_cmd->begin_redirs = begin_redirs;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

//функция проверяет, передали ли новый и если начало не 0,
// добавляет его в конец, а если 0 - возвращает новый как начало
t_cmd	**ft_cmd_add_back(t_cmd *new_cmd, t_cmd **begin_cmd)
{
	t_cmd	*last;

	if (!new_cmd)
		return (ft_free_cmd_list(begin_cmd));
	last = *begin_cmd;
	if (!last)
	{
		*begin_cmd = new_cmd;
		return (begin_cmd);
	}
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	return (begin_cmd);
}

//проставляет файлам значение поле "предыдущий"
void	ft_cmd_prev_setter(t_cmd *cmd_begin)
{
	t_cmd	*prev;

	while (cmd_begin && cmd_begin->next)
	{
		prev = cmd_begin;
		cmd_begin = cmd_begin->next;
		cmd_begin->prev = prev;
	}
}
