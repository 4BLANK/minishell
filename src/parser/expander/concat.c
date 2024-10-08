/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:04:35 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 12:04:36 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*allocate_first_char(char *src);
static char	*handle_null_cases(char *dest, char *src, char *tmp, int f);

char	*concat(char *dest, char *src, int flag)
{
	char	*new_dest;
	char	*holder;
	char	*result;
	size_t	len;

	holder = NULL;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (flag == 1)
		holder = allocate_first_char(src);
	result = handle_null_cases(dest, src, holder, flag);
	if (result != NULL)
		return (result);
	len = ft_strlen(dest) + ft_strlen(src) + 1;
	new_dest = (char *)malloc(len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(new_dest, dest, len);
	if (flag == 1)
		ft_strlcat(new_dest, holder, len);
	else
		ft_strlcat(new_dest, src, len);
	free(dest);
	free(holder);
	return (new_dest);
}

static char	*allocate_first_char(char *src)
{
	char	*holder;

	holder = (char *)malloc(2 * sizeof(char));
	if (holder == NULL)
		return (NULL);
	holder[0] = src[0];
	holder[1] = '\0';
	return (holder);
}

static char	*handle_null_cases(char *dest, char *src, char *tmp, int f)
{
	if (src == NULL)
		return (free(tmp), dest);
	if (dest == NULL)
	{
		if (f == 1)
			return (tmp);
		return (free(tmp), ft_strdup(src));
	}
	return (NULL);
}
