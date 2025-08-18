/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:03:05 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:03:08 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_safe(const char *s)
{
	size_t	len;
	char	*d;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s) + 1;
	d = malloc(len);
	if (d)
		ft_memcpy(d, s, len);
	return (d);
}
