/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:02:33 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:23:45 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_key_val(char *key, char *val)
{
	size_t	len_key;
	size_t	len_val;
	char	*out;

	len_key = ft_strlen(key);
	len_val = 0;
	if (val)
		len_val = ft_strlen(val);
	if (val)
		out = malloc(len_key + len_val + 2);
	else
		out = malloc(len_key + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, key, len_key);
	if (val)
	{
		out[len_key] = '=';
		ft_memcpy(out + len_key + 1, val, len_val);
		out[len_key + len_val + 1] = '\0';
	}
	else
		out[len_key] = '\0';
	return (out);
}

static t_env	*ft_create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = NULL;
	if (value)
		new_node->value = ft_strdup(value);
	new_node->kv = ft_strjoin_key_val(key, value);
	if (!new_node->kv || !new_node->key)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node->kv);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = ft_create_env_node(key, value);
	if (!new_node)
		return ;
	if (!*env)
		*env = new_node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
