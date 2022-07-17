/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_creators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:23 by keaton            #+#    #+#             */
/*   Updated: 2022/07/16 20:22:24 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//проверяет, передали ли новый и если начало не 0,
// добавляет его в конец, а если 0 - возвращает новый как начало
t_tkn	**ft_tkn_add_back(t_tkn *new_tkn, t_tkn **begin_tkn)
{
	t_tkn	*last;

	if (!new_tkn)
		return (ft_free_tkn_list(begin_tkn));
	last = *begin_tkn;
	if (!last)
	{
		*begin_tkn = new_tkn;
		return (begin_tkn);
	}
	while (last->next)
	{
		last = last->next;
	}
	last->next = new_tkn;
	return (begin_tkn);
}

//инициализирует токен символа, заполняя нужные значения и возвращает его адрес
t_tkn	*ft_symb_tkn_init(char symb, int count)
{
	t_tkn	*new_tkn;

	new_tkn = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_tkn)
		return (NULL);
	new_tkn->type = ft_def_token_type(symb, count);
	new_tkn->value = NULL;
	new_tkn->next = NULL;
	new_tkn->prev = NULL;
	return (new_tkn);
}

//заполняет значение токена текста и возвращает его адрес.
//Также двигает строку до конца строки,
// токена символа или пробела c учетом ковычек
char	*ft_cmd_value_init(char **cmd)
{
	char	*cmd_value;
	char	*start;
	int		quote_type;

	quote_type = 0;
	start = *cmd;
	while (quote_type || (!ft_is_symb_token(**cmd) && !ft_isspace(**cmd)
			&& **cmd))
		quote_type = ft_quotes_identifier((*cmd)++, &quote_type);
	cmd_value = (char *)malloc(sizeof(char) * (*cmd - start + 1));
	if (!cmd_value)
		return (NULL);
	ft_strlcpy(cmd_value, start, *cmd - start + 1);
	return (cmd_value);
}

//инициализирует токен текста, заполняя нужные значения и возвращает его адрес.
//Также двигает строку до конца строки, токена символа или пробела
t_tkn	*ft_cmd_tkn_init(char **cmd)
{
	t_tkn	*new_tkn;

	new_tkn = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_tkn)
		return (NULL);
	new_tkn->type = 1;
	new_tkn->value = ft_cmd_value_init(cmd);
	if (!new_tkn->value)
	{
		free(new_tkn);
		return (NULL);
	}
	new_tkn->next = NULL;
	return (new_tkn);
}

//проверяет, являются ли символы строки токеном symb и если да,
// создаёт соответствующий токен и двигает строку
t_tkn	**ft_tkn(char **cmd, t_tkn **tkn_begin, char symb, int maxlen)
{
	int		count;

	count = 0;
	while (**cmd == symb && count < maxlen)
	{
		count++;
		(*cmd)++;
	}
	if (count > 0)
		tkn_begin = ft_tkn_add_back(ft_symb_tkn_init(symb, count), tkn_begin);
	return (tkn_begin);
}
