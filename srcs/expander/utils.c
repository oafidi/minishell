/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:43:23 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/18 15:17:31 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_and_add_quotes(char *value)
{
	char	*result;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!value)
		return (NULL);
	result = remove_quotes(value);
	free(value);
	if (!result || !(*result))
		return (result);
	value = malloc(sizeof(char) * (ft_strlen(result) + 3));
	value[i++] = '"';
	while (result[j])
		value[i++] = result[j++];
	value[i++] = '"';
	value[i] = '\0';
	free(result);
	return (value);
}

static char	*extract_var_name(char *str, int *len)
{
	char	*var_name;
	int		i;

	*len = 0;
	if (!str || !is_valid_var_start(str[0]))
		return (NULL);
	while (str[*len] && is_valid_var_char(str[*len]))
		(*len)++;
	var_name = malloc(sizeof(char) * (*len + 1));
	if (!var_name)
		return (NULL);
	i = -1;
	while (++i < *len)
		var_name[i] = str[i];
	var_name[i] = '\0';
	return (var_name);
}

char	*expand_variable(char *str, int *i, t_env *env_list)
{
	char	*var_value;
	char	*var_name;
	int		var_len;

	if (str[*i + 1] == '?')
		return (*i += 2, ft_itoa(*exit_status_get()));
	var_name = extract_var_name(str + *i + 1, &var_len);
	if (!var_name && var_len == 0)
		return ((*i)++, ft_strdup("$"));
	if (!var_name)
		return (NULL);
	*i += var_len + 1;
	var_value = get_env_value(env_list, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}
