/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 06:26:24 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/03 03:26:39 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2, char delimiter)
{
	size_t		len;
    char		*dest;
	size_t		i;
	size_t		j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len + 2));
	if (!dest)
		return (free(s1), NULL);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = delimiter;
    j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (free(s1), dest);
}
