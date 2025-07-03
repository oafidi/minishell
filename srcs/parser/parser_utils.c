#include "../../includes/minishell.h"

t_cmd   *create_command(void)
{
    t_cmd   *cmd;
    
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->argc = 0;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

t_redir *create_redirection(t_token_type type, char *target)
{
    t_redir *redir;
    
    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->target = ft_strdup(target);
    if (!redir->target)
    {
        free(redir);
        return (NULL);
    }
    redir->heredoc_content = NULL;
    redir->heredoc_expand = 1;
    redir->next = NULL;
    return (redir);
}