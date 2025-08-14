/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_strlen_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:48:15 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/13 17:23:04 by yettalib         ###   ########.fr       */
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

int	ft_parse_export_arg(char *arg, char **key,
			char **value, int *append)
{
	char	*plus_pos;
	char	*eq_pos;

	*append = 0;
	plus_pos = ft_strstr(arg, "+=");
	if (plus_pos)
	{
		*append = 1;
		*key = ft_strndup(arg, plus_pos - arg);
		*value = ft_strdup(plus_pos + 2);
		return (ft_is_valid_identifier(*key));
	}
	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
	{
		*key = ft_strndup(arg, eq_pos - arg);
		*value = ft_strdup(eq_pos + 1);
		return (ft_is_valid_identifier(*key));
	}
	*key = ft_strdup(arg);
	*value = NULL;
	return (ft_is_valid_identifier(*key));
}
