/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:32:54 by mzelouan          #+#    #+#             */
/*   Updated: 2023/11/19 06:17:01 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*dst;
	size_t	start;
	size_t	end;
	char *holder;

	if (!s1)
		return (NULL);
	holder = ft_strdup(s1);
	if (!set)
		return (holder);
	free(holder);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	dst = ft_substr(s1, start, end - start + 1);
	free(s1);
	return (dst);
}
