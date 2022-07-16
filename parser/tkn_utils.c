/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:27 by keaton            #+#    #+#             */
/*   Updated: 2022/07/16 20:22:28 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tkn(t_tkn	*tkn)
{
	if (tkn->value)
		free(tkn->value);
	free(tkn);
}

t_tkn	**ft_free_tkn_list(t_tkn **begin_tkn)
{
	//проверяет, передали ли начало и если да, то фришит строки и токены
	t_tkn	*active;
	t_tkn	*prev;

	if (!*begin_tkn)
		return (NULL);
	active = *begin_tkn;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_tkn(prev);
		prev = active;
	}
	ft_free_tkn(active);
	*begin_tkn = NULL;
	return (NULL);
}

void	ft_tkn_del(t_tkn *tkn, t_tkn **begin_tkn)//надо написать удаление текста из токенов. похоже нужно будет поле предыдущий в токенах
{
	t_tkn	*prev;
	t_tkn	*next;

	prev = tkn->prev;
	next = tkn->next;
	if (prev)
		prev->next = next;
	else
	{
		if (next)
			*begin_tkn = tkn->next;
		else
			*begin_tkn = NULL;
	}
	if (next)
		next->prev = prev;
	ft_free_tkn(tkn);
}

void ft_tkn_prev_setter(t_tkn **tkn_begin)
{
//проставляет файлам значение поле "предыдущий"
	t_tkn	*prev;

	while (*tkn_begin && (*tkn_begin)->next)
	{
		prev = *tkn_begin;
		tkn_begin = &(*tkn_begin)->next;
		(*tkn_begin)->prev = prev;
	}
}

/*
заглушка - 0
текст - 1
пайп - 2
< - 3
> - 4
<< - 5
>> - 6
пробел - 7
*/

int ft_def_token_type(char symb, int count)
{
	//определяет тип полученного символа для присвоения индекса токену
	int	type;

	type = 0; //это заглушка
	if (count == 1)
	{
		if (symb == '|')
			type = 2;
		else if (symb == '<')
			type = 3;
		else if (symb == '>')
			type = 4;
		else if (symb == ' ')
			type = 7;
	}
	else if (count == 2)
	{
		if (symb == '<')
			type = 5;
		else if (symb == '>')
			type = 6;
	}
	return (type);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f');
}

int	ft_is_symb_token(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ft_tkn_len_counter(t_tkn *tkn, char **env)
{
	//считает длину строки, которая получится для имени файла после раскрытия ковычек
	char	*str;
	int		len;
	int		quote_type;

	quote_type = 0;
	len = 0;
	str = tkn->value;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, &quote_type);
		else if (*str == '$' && (!quote_type || !(quote_type == 2)) && tkn->type != 5)
		{
			if (*(++str) == '?')
			{
				len += ft_numlen(g_error);
				str++;
			}
			else
				len += ft_var_len(&(str), env);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}
