/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:06 by keaton            #+#    #+#             */
/*   Updated: 2022/07/31 19:56:05 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_file(t_file	*tkn)
{
	if (tkn->name)
		free(tkn->name);
	free(tkn);
}

void	*error_print(int err_num, char *err_char)
{
	g_error = err_num;
	write(2, err_char, ft_strlen(err_char));
	write(2, "\n", 1);
	return (NULL);
}

//проверяет, передали ли начало и если да, то фришит строки и токены
t_file	**ft_free_file_list(t_file **begin_file)
{
	t_file	*active;
	t_file	*prev;

	if (!begin_file || !*begin_file)
		return (NULL);
	active = *begin_file;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_file(prev);
		prev = active;
	}
	ft_free_file(active);
	*begin_file = NULL;
	return (NULL);
}

//инициализирует файл с атрибутами, заполняет нужные значения
// и возвращает его адрес
t_file	*ft_file_init(char *name, int type)
{
	t_file	*new_file;

	if (!name)
		return (NULL);
	new_file = (t_file *)malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->name = name;
	new_file->type = type;
	new_file->next = NULL;
	return (new_file);
}

//функция проверяет, передали ли новый и если начало не 0, добавляет его в конец
// а если 0 - возвращает новый как начало
t_file	**ft_file_add_back(t_file *new_file, t_file **begin_file)
{
	t_file	*last;

	if (!new_file)
		return (ft_free_file_list(begin_file));
	last = *begin_file;
	if (!last)
	{
		*begin_file = new_file;
//		printf("%p", begin_file);
//		ft_print_file2(*begin_file);
		return (begin_file);
	}
	while (last->next)
		last = last->next;
	last->next = new_file;
	return (begin_file);
}


