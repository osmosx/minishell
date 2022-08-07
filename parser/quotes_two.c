/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:18 by keaton            #+#    #+#             */
/*   Updated: 2022/08/07 21:28:02 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//раскрывает скобки в названии файла в заранее
// замалоченную переменную нужного размера
void	ft_dequote_tkn_value(t_tkn *tkn, char *value, char **env)
{
	char	*str;
	int		quote_type;

	quote_type = 0;
	str = tkn->value;
	printf("value = %s\n", str);
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, &quote_type);
		else if (*str == '$' && quote_type != 1	&& tkn->type != 5)
		{
			if (*(++str) == '?')
				value = ft_fill_last_err(value, &str);
			else if (*str && !ft_isspace(*str) && !ft_is_opening_or_closing_quote(*str, quote_type))
				value = ft_fill_var_value(&str, value, env);
			else
				*(value++) = '$';
		}
		else
			*(value++) = *(str++);
	}
}

//раскрывает скобки в названии файла
t_tkn	*ft_tkn_dequoter(t_tkn *tkn, char **env)
{
	int		len;
	char	*value;

	if (tkn && tkn->value)
	{
		len = ft_tkn_len_counter(tkn, env);
		printf ("tknlen = %d\n", len);
		value = (char *)malloc((len + 1) * sizeof(char));
		if (!value)
			return (NULL);
		value[len] = '\0';
		ft_dequote_tkn_value(tkn, value, env);
		free(tkn->value);
		tkn->value = value;
	}
	return (tkn);
}

//раскроетывает скобки в оставшихся командах
t_tkn	**ft_dequote_tkn_list(t_tkn **tkn_begin, char **env)
{
	t_tkn	*tkn;
	t_tkn	*res;

	tkn = *tkn_begin;
	while (tkn)//->next)
	{
		while (tkn->type == 7 && tkn->next)
		{
			res = tkn;
			tkn = tkn->next;
			ft_tkn_del(res, tkn_begin);
		}
		if (tkn->type != 1 && tkn->type != 7)
			printf("Something other than words token left in list");
		if (!ft_tkn_dequoter(tkn, env))
			return (ft_free_tkn_list(tkn_begin));
		if (tkn)
			tkn = tkn->next;
	}
	// if (tkn->type == 7)
	// {
	// 	res = tkn;
	// 	tkn = tkn->prev;
	// 	ft_tkn_del(res, tkn_begin);
	// }
	// if (!tkn)
	// 	return (ft_tkn_add_back(ft_symb_tkn_init('0', 0), tkn_begin));
	// if (!ft_tkn_dequoter(tkn, env))
	// 	return (ft_free_tkn_list(tkn_begin));
	return (tkn_begin);
}