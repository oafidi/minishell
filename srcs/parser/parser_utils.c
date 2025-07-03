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

void    add_redirection_to_cmd(t_cmd *cmd, t_redir *redir)
{
    t_redir *current;
    
    if (!cmd || !redir)
        return;
    if (!cmd->redirs)
        cmd->redirs = redir;
    else
    {
        current = cmd->redirs;
        while (current->next)
            current = current->next;
        current->next = redir;
    }
}

int validate_syntax(t_token *tokens)
{
    while (tokens && tokens->type != TOKEN_END)
    {
        if (!check_pipe_errors(tokens))
            return (0);
        if (!check_redir_errors(tokens))
            return (0);
        tokens = tokens->next;
    }
    if (!check_pipe_end(tokens))
        return (0);
    return (1);
}

int count_command_args(t_token *start)
{
    int     count;
    t_token *current;

    count = 0;
    current = start;
    while (current && current->type != TOKEN_PIPE && current->type != TOKEN_END)
    {
        if (current->type == TOKEN_WORD)
            count++;
        else if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
            current = current->next;
        current = current->next;
    }
    return (count);
}
