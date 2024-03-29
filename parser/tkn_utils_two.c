/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:27 by keaton            #+#    #+#             */
/*   Updated: 2022/08/07 21:28:37 by keaton           ###   ########.fr       */
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
int	ft_tkn_len_counter(t_tkn *tkn, char **env, int qt)
{
	char	*str;
	int		len;

	len = 0;
	str = tkn->value;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, qt))
			qt = ft_quotes_identifier(str, &qt);
		else if (*str == '$' && qt != 1 && tkn->type != 5)
		{
			if (*(++str) == '?')
				len += ft_numlen(g_error);
			else if (*str && !ft_isspace(*str)
				&& !ft_is_opening_or_closing_quote(*str, qt))
				len += ft_var_len(&(str), env);
			else
				len++;
		}
		else
			len++;
		if (*str)
			str++;
	}
	return (len);
}
