/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:14 by keaton            #+#    #+#             */
/*   Updated: 2022/08/07 19:29:57 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//считает длину числа в символах
int	ft_numlen(int n)
{
	int		count;

	if (n <= 0)
	{
		count = 1;
		n *= -1;
	}
	else
		count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

//ф-ция считает дляну переменной, двигает строку на лен вперед и на 1 назад
int	ft_var_len(char **str, char **env)
{
	int		len;
	char	*ptr;

	ptr = *str;
	len = 0;
	while (ft_isalnum(*ptr) || *ptr == '_')
	{
		ptr++;
		len++;
	}
	ptr = NULL;
	while (*env)
	{
		if (!ft_strncmp(*str, *env, len) && *(*env + len) == '=')
			ptr = (*env) + len + 1;
		env++;
	}
	(*(str--)) += len;
	if (ptr)
		return ((int)ft_strlen(ptr));
	else
		return (0);
}

//проверяет, является ли символ реальными открывающими или закрывающими скобками
int	ft_is_opening_or_closing_quote(char c, int qt)
{
	if ((c == '"' && (!qt || qt == 2)) || (c == '\'' && (!qt || qt == 1)))
		return (1);
	else
		return (0);
}

//заполняет в строку "имя" номер посл ошибки итоа и возвращает
// адрес первого незаполненного символа, делает (*str)++
char	*ft_fill_last_err(char *name, char **str)
{
	char	*num;
	int		i;

	num = NULL;
	i = 0;
	while (!num && i++ < 5)
		num = ft_itoa(g_error);
	(*str)++;
	i = 0;
	while (num[i])
		*(name++) = num[i++];
	*(name++) = num[i++];
	free(num);
	return (name);
}

//ищет перем по имени из букв до не (словоцифры или НП),
// заполняет имя её значением и сдвигает строку
char	*ft_fill_var_value(char **str, char *name, char **env)
{
	int		len;
	char	*ptr;

	ptr = *str;
	len = 0;
	while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
	{
		ptr++;
		len++;
	}
	ptr = NULL;
	while (*env)
	{
		if (!ft_strncmp(*str, *env, len) && *(*env + len) == '=')
			ptr = (*env) + len + 1;
		env++;
	}
	(*str) += len;
	while (ptr && *ptr)
		*(name++) = *(ptr++);
	return (name);
}
