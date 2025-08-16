#include "../../includes/minishell.h"

static char	*create_new_value(char *old_value, char *value, int is_append)
{
	if (is_append && old_value && *old_value)
		return (ft_strjoin(old_value, value, '\0'));
	return (free(old_value), ft_strdup(value));
}

static void	update_existing_var(t_env *existing, char *key, char *value,
		int is_append)
{
	if (value)
	{
		existing->value = ft_create_new_value(existing->value, value, is_append);
        free(existing->kv);
		existing->kv = join_kv(key, existing->value);
	}
}

static t_env	*find_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	update_env_var(t_env **env, char *key, char *value, int append)
{
	t_env	*existing;

	existing = find_env_var(*env, key);
	if (existing)
		update_existing_var(existing, key, value, append);
	else
		ft_lstadd_back(env, key, value);
}

static int	parse_export_arg(char *arg, char **key, char **value, int *append)
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
		return (is_valid_identifier(*key));
	}
	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
	{
		*key = ft_strndup(arg, eq_pos - arg);
		*value = ft_strdup(eq_pos + 1);
		return (is_valid_identifier(*key));
	}
	*key = ft_strdup(arg);
	*value = NULL;
	return (is_valid_identifier(*key));
}

int process_export_arg(char *arg, t_env **env)
{
	char	*key;
	char	*value;
	int		is_append;

    key = NULL;
    value = NULL;
	if (parse_export_arg(arg, &key, &value, &is_append))
	{
		update_env_var(env, key, value, is_append);
		if (key)
			free(key);
		if (value)
			free(value);
		return (0);
	}
	ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
	if (key)
		free(key);
	if (value)
		free(value);
	return (1);
}
