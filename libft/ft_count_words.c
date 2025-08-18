/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:02:40 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:02:42 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_result(char *res, char start, char *s, char last)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (start)
		res[i++] = start;
	while (s && s[j])
		res[i++] = s[j++];
	if (last)
		res[i++] = last;
	res[i] = '\0';
}

static char	*join_three(char start, char *s, char last)
{
	size_t	len;
	size_t	add;
	char	*res;

	len = 0;
	if (s)
		len = ft_strlen(s);
	add = 0;
	if (start)
		add++;
	if (last)
		add++;
	res = malloc(len + add + 1);
	if (!res)
		return (NULL);
	fill_result(res, start, s, last);
	return (res);
}

int	count_words(char start, char *s, char last)
{
	int		count;
	char	*temp;
	int		i;

	temp = join_three(start, s, last);
	if (!temp)
		return (0);
	i = 0;
	count = 0;
	while (temp[i])
	{
		while (is_space(temp[i]))
			i++;
		if (temp[i])
			count++;
		while (temp[i] && !is_space(temp[i]))
			i++;
	}
	free(temp);
	return (count);
}

void	free_args(char **p, int n_words)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	if (n_words == -1)
	{
		while (p[i])
		{
			free(p[i]);
			i++;
		}
	}
	else
	{
		while (i < n_words)
		{
			free(p[i]);
			i++;
		}
	}
	free(p);
}
