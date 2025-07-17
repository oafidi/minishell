#include "../../../includes/minishell.h"

t_env	*copy_environment(char **env)
{
    return (NULL);
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
