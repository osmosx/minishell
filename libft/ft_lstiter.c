/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:37:16 by nenvoy            #+#    #+#             */
/*   Updated: 2021/10/19 15:08:09 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*element;

	element = lst;
	if (f != NULL)
	{
		while (element != NULL)
		{
			f(element->content);
			element = element -> next;
		}
	}
}
