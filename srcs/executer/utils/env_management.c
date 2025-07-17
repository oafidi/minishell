#include "../../../includes/minishell.h"

static size_t	get_equal_index(const char *str)
{
	size_t	i = 0;

	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static t_env	*create_node(const char *str)
{
	t_env	*node;
	size_t	eq_idx;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq_idx = get_equal_index(str);
	node->key = ft_substr(str, 0, eq_idx);
	if (str[eq_idx] == '=')
		node->value = ft_strdup(str + eq_idx + 1);
	else
		node->value = ft_strdup("");
	node->next = NULL;
	return (node);
}

t_env	*copy_environment(char **env)
{
	t_env	*head = NULL;
	t_env	*last = NULL;
	t_env	*new;

	while (env && *env)
	{
		new = create_node(*env);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		env++;
	}
	return (head);
}

void	free_environment(t_env **env)
{
	t_env	*next;

	while (*env)
	{
		next = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = next;
	}
}
