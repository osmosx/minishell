/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:36:08 by nenvoy            #+#    #+#             */
/*   Updated: 2021/10/19 14:36:08 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*i;
	t_list	*c;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	i = *lst;
	while (i -> next)
		i = i -> next;
	c = new;
	i -> next = c;
}
