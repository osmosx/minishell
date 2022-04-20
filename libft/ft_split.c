/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:36:08 by nenvoy            #+#    #+#             */
/*   Updated: 2021/10/19 14:36:08 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words_count(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i++] == c)
			continue ;
		words++;
		while (s[i] != c)
			if (s[i++] == '\0')
				return (words);
	}
	return (words);
}

static size_t	ft_words_len(const char *s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != sep)
		i++;
	return (i);
}

static char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	arr = malloc((ft_words_count(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i++] == c)
			continue ;
		--i;
		arr[j] = ft_substr(s, i, ft_words_len(&s[i], c));
		if (arr[j++] == NULL)
			return (ft_free (arr));
		i += ft_words_len(&s[i], c);
	}
	arr[j] = 0;
	return (arr);
}
