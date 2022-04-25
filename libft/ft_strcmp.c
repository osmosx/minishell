/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:36:08 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/21 14:36:08 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//int	ft_strcmp(const char *s1, const char *s2)
//{
//	int	i;
//
//	i = 0;
//	if (ft_strlen(s1) != ft_strlen(s2))
//		return (0);
//	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
//		i++;
//	if ((s1[i] - s2[i]) != 0)
//		return (0);
//	return (1);
//}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
