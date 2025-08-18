/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:02:00 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:02:01 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*last_occr;

	last_occr = NULL;
	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			last_occr = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)last_occr);
}
