/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:27 by keaton            #+#    #+#             */
/*   Updated: 2022/07/16 20:22:28 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f');
}

int	ft_is_symb_token(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

//считает длину строки, которая получится для имени файла
// после раскрытия ковычек
int	ft_tkn_len_counter(t_tkn *tkn, char **env)
{
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
		else if (*str == '$' && (!quote_type || quote_type != 2)
			&& tkn->type != 5)
		{
			if (*(++str) == '?')
				len += ft_numlen(g_error);
			else
				len += ft_var_len(&(str), env);
		}
		else
			len++;
		str++;
	}
	return (len);
}

