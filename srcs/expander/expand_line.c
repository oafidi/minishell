#include "../../includes/minishell.h"


static int is_export_case(char *line)
{
    (void)line; 
    return (0);
}

static char    *expand(char *line, global_struct *global_struct)
{
    char	*result;
    int		i;
    int		quote_state;

    if (!line || !global_struct)
        return (NULL);
    result = ft_strdup("");
    if (!result)
        return (NULL);
    i = 0;
    quote_state = NO_QUOTE;
    while (line[i])
    {
        if ((line[i] == '\'' || line[i] == '"'))
        {
            if (line[i] != get_quote_char(quote_state) && quote_state != NO_QUOTE)
                result = ft_strjoin_char(result, line[i], 0);
            update_quote_state(line[i], &quote_state);
            i++;
        }
        else if (line[i] == '$' && quote_state != SINGLE_QUOTE)
        {
            char *var_expansion = expand_variable(line, &i, global_struct->env,
                                                  global_struct->last_exit_status);
            if (var_expansion)
            {
                result = ft_strjoin(result, var_expansion, 0);
                free(var_expansion);
            }
        }
        else
        {
            result = ft_strjoin_char(result, line[i], 0);
            i++;
        }
        if (!result)
            return (NULL);
    }
    return (result);
}

void	expand_line(t_cmd *cmd, global_struct *global_struct)
{
    char	*expanded;

    if (!cmd || !cmd->line || !global_struct)
        return ;
    if (is_export_case(cmd->line))
    {}
    else
    {
        expanded = expand(cmd->line, global_struct);
		free(cmd->line);
    }
    cmd->line = expanded;
}