/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:01 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:50:04 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
	return (NULL);
}

char	**add_line(char **arr, char *new_line)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i++] = ft_strdup(new_line);
	new_arr[i] = NULL;
	ft_free(arr);
	return (new_arr);
}
