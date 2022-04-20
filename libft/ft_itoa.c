/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:36:09 by nenvoy            #+#    #+#             */
/*   Updated: 2021/10/19 14:36:09 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenght(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	c;

	c = n;
	len = ft_lenght(c);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	if (c == 0)
		str[0] = '0';
	while (c)
	{
		if (c < 0)
		{
			str[0] = '-';
			c *= -1;
		}
		str[len] = c % 10 + 48;
		c /= 10;
		len--;
	}
	return (str);
}
