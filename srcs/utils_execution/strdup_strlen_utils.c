/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_strlen_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:48:15 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/18 17:01:14 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_execution(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	result = (char *)malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

int	ft_is_valid_identifier(char *arg)
{
	int	i;

	if (!is_valid_var_start(arg[0]))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
	{
		if (!is_valid_var_char(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_handle_assignment(char *arg, char **key, char **value,
					int *append)
{
	char	*plus_pos;
	char	*eq_pos;

	plus_pos = ft_strstr(arg, "+=");
	if (plus_pos)
	{
		*append = 1;
		*key = ft_strndup(arg, plus_pos - arg);
		*value = ft_strdup(plus_pos + 2);
		return (1);
	}
	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
	{
		*key = ft_strndup(arg, eq_pos - arg);
		*value = ft_strdup(eq_pos + 1);
		return (1);
	}
	return (0);
}

int	ft_parse_export_arg(char *arg, char **key, char **value, int *append)
{
	*append = 0;
	if (ft_handle_assignment(arg, key, value, append))
	{
		if (!*key || !*value)
			return (free(*key), free(*value), 0);
		return (1);
	}
	*key = ft_strdup(arg);
	*value = NULL;
	if (!*key)
		return (0);
	return (1);
}
