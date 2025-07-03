#include "../../includes/minishell.h"

int check_pipe_errors(t_token *tokens)
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

int check_redir_errors(t_token *tokens)
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

int check_pipe_end(t_token *tokens)
{
    if (tokens && tokens->prev && tokens->prev->type == TOKEN_PIPE)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (0);
    }
    return (1);
}

void	cleanup_command_on_error(t_cmd *cmd, int i)
{
	while (--i >= 0)
		free(cmd->args[i]);
	free(cmd->args);
	free_redirections(cmd->redirs);
	free(cmd);
}