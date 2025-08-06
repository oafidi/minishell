#include "../../includes/minishell.h"

static char    *build_line_from_env(t_env *env, global_struct *global_struct)
{
    char    *line;
    char    *temp;

    if (!env || !global_struct)
        return (free_environment(&env), NULL);
    temp = ft_strdup(env->key);
    line = ft_strjoin(env->key, "=", 0);
    env->key = temp;
    if (!line)
        return (free_environment(&env), NULL);
    if (env->value)
    {
        temp = ft_strjoin(line, env->value, 0);
        line = temp;
    }
    return (free_environment(&env), line);
}

static char *remove_and_add_quotes(char *value)
{
    char *result;
    int i = 0;
    int j = 0;

    if (!value)
        return (NULL);
    result = remove_quotes(value);
    free(value);
    if (!result)
        return (NULL);
    value = malloc(sizeof(char) * (ft_strlen(result) + 3));
    value[i++] = '"';
    while (result[j])
        value[i++] = result[j++];
    value[i++] = '"';
    value[i] = '\0';
    free(result);
    return (value);
}
static char    *expand_env_value(char *value, int should_split, global_struct *global_struct)
{
    char    *result;
    char    **arr;
    int     i;

    //printf("Expanding value: %s\n", value);
    result = expand(value, global_struct);
    if (!result)
        return (free(value), NULL);
    i = 0;
    arr = NULL;
    if (should_split)
    {
        //printf("Splitting value: %s\n", result);
        arr = line_to_args(result);
        free(result);
        if (!arr)
            return (NULL);
        result = NULL;
        while (arr[i])
            value = ft_strjoin(result, arr[i++], ' ');
    }
    else
        result = remove_and_add_quotes(result);
    return (free_args(arr, i), result);
}

static char *expand_arg(char *arg, int should_split, global_struct *global_struct)
{
    t_env   *env;
    char    *temp;
    int     should_split_value;

    if (!arg || !global_struct)
        return (NULL);
    env = create_node(arg);
    if (!env)
        return (NULL);
    temp = env->key;
    //printf("should_split: %d, key: %s\n", should_split, env->key);
    should_split_value = should_split || (check_quotes_type(env->key) != NO_QUOTE);
    env->key = expand(temp, global_struct);
    //printf("Expanded key: %s\n", env->key);
    free(temp);
    if (!env->key)
        return (free_environment(&env), NULL);
    temp = env->value;
    //printf("Expanding value for vla: %s\n", env->value);
    env->value = expand_env_value(temp, should_split_value, global_struct);
    free(temp);
    // if (!env->value)
    //     return (printf("wwa\n"),free_environment(&env), NULL);
    return (build_line_from_env(env, global_struct));
}

char *expand_export(char *line, global_struct *global_struct)
{
    int     should_split;
    char    *expanded;
    char    *result;
    char    **arr;
    int     i;

    if (!line || !global_struct)
        return (NULL);
    //printf("Expanding export line: %s\n", line);
    arr = line_to_args(line);
    if (!arr)
        return (NULL);
    should_split = (check_quotes_type(arr[0]) != NO_QUOTE);
    i = 0;
    result = NULL;
    while (arr[i])
    {
        //printf("Expanding arg: %s\n", arr[i]);
        expanded = expand_arg(arr[i], should_split, global_struct);
        if (!expanded)
            return (free_args(arr, i), NULL);
        //printf("Expanded arg: %s\n", expanded);
        result = ft_strjoin(result, expanded, ' ');
        free(expanded);
        if (!result)
            return (free_args(arr, i), NULL);
        i++;
    }
    return (free_args(arr, i),result);
}
