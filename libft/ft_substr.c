/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:36:09 by nenvoy            #+#    #+#             */
/*   Updated: 2021/10/19 14:36:09 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substr = (char *) malloc ((len + 1));
	if (substr == NULL)
		return (NULL);
	if (start >= ft_strlen (s))
	{
		substr[i] = '\0';
		return (substr);
	}
	while (len != 0 && s[start] != '\0')
	{
		substr[i++] = s[start++];
		len--;
	}
	substr[i] = '\0';
	return (substr);
}
