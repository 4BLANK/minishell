/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:51:19 by mzelouan          #+#    #+#             */
/*   Updated: 2023/11/19 01:13:31 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*node;

	if (new_node != NULL)
	{
		if (*lst == NULL)
			*lst = new_node;
		else
		{
			node = *lst;
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = new_node;
		}
	}
}
