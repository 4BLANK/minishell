/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:03:02 by mzelouan          #+#    #+#             */
/*   Updated: 2023/11/19 18:14:45 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)malloc(len * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, len);
	ft_strlcat(dst, s2, len);
	return (dst);
}
