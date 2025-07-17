#include "../../includes/minishell.h"

static int check_pipe_errors(t_token *tokens)
{
    if (tokens->type == TOKEN_PIPE && tokens->prev == NULL)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        return (0);
    }
    if (tokens->type == TOKEN_PIPE && tokens->prev && tokens->prev->type == TOKEN_PIPE)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        return (0);
    }
    return (1);
}

static int check_redir_errors(t_token *tokens)
{
    if (tokens->type >= TOKEN_REDIR_IN && tokens->type <= TOKEN_HEREDOC)
    {
        if (!tokens->next || tokens->next->type != TOKEN_WORD)
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            return (0);
        }
    }
    return (1);
}

static int check_pipe_end(t_token *tokens)
{
    if (tokens && tokens->prev && tokens->prev->type == TOKEN_PIPE)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (0);
    }
    return (1);
}

int validate_syntax(t_token *tokens, global_struct *global_struct)
{
    while (tokens && tokens->type != TOKEN_END)
    {
        if (!check_pipe_errors(tokens))
            return (global_struct->last_exit_status = 258, 0);
        if (!check_redir_errors(tokens))
            return (global_struct->last_exit_status = 258, 0);
        tokens = tokens->next;
    }
    if (!check_pipe_end(tokens))
        return (global_struct->last_exit_status = 258, 0);
    return (1);
}