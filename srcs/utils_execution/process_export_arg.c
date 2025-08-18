/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:02:02 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/18 17:43:13 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_create_new_value(char *old_value, char *value, int is_append)
{
	if (is_append && old_value && *old_value)
		return (ft_strjoin(old_value, value, '\0'));
	return (free(old_value), ft_strdup(value));
}

static void	ft_update_existing_var(t_env *existing, char *key, char *value,
		int is_append)
{
	if (value)
	{
		existing->value = ft_create_new_value(existing->value,
				value, is_append);
		free(existing->kv);
		existing->kv = ft_strjoin_key_val(key, existing->value);
	}
}

static t_env	*ft_find_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	ft_update_env_var(t_env **env, char *key, char *value, int append)
{
	t_env	*existing;

	existing = ft_find_env_var(*env, key);
	if (existing)
		ft_update_existing_var(existing, key, value, append);
	else
		ft_lstadd_back(env, key, value);
}

int	process_export_arg(char *arg, t_env **env)
{
	char	*key;
	char	*value;
	int		is_append;

	key = NULL;
	value = NULL;
	if (ft_parse_export_arg(arg, &key, &value, &is_append))
	{
		if (ft_is_valid_identifier(key))
		{
			ft_update_env_var(env, key, value, is_append);
			free(key);
			free(value);
			return (0);
		}
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	free(key);
	free(value);
	return (1);
}
