/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:36:08 by nenvoy            #+#    #+#             */
/*   Updated: 2021/10/19 14:36:08 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	j = ft_strlen (dst);
	srclen = ft_strlen (src);
	dstlen = ft_strlen (dst);
	i = 0;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	if (dstsize > dstlen)
	{
		while (src[i] != '\0' && j < dstsize - 1)
		{
			dst[j++] = src[i++];
		}
		dst[j] = '\0';
	}
	return (dstlen + srclen);
}
