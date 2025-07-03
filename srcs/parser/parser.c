#include "../../includes/minishell.h"

static t_cmd	*parse_single_command(t_token **token_ptr)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = init_command_parsing(*token_ptr);
	if (!cmd)
		return (NULL);
	while (*token_ptr && (*token_ptr)->type != TOKEN_PIPE
		&& (*token_ptr)->type != TOKEN_END)
	{
		if ((*token_ptr)->type == TOKEN_WORD)
		{
			if (!parse_word_token(cmd, token_ptr, &i))
				return (cleanup_command_on_error(cmd, i), NULL);
		}
		else if ((*token_ptr)->type >= TOKEN_REDIR_IN
			&& (*token_ptr)->type <= TOKEN_HEREDOC)
		{
			if (!parse_redirection_token(cmd, token_ptr))
				return (cleanup_command_on_error(cmd, i), NULL);
		}
	}
	return (cmd->argc = i, cmd->args[i] = NULL, cmd);
}

static t_cmd   *parse_pipeline(t_token **token_ptr)
{
    t_cmd *head;
    t_cmd *tail;
    t_cmd *new_cmd;
    
    head = NULL;
    tail = NULL;
    while (*token_ptr && (*token_ptr)->type != TOKEN_END)
    {
        new_cmd = parse_single_command(token_ptr);
        if (!new_cmd)
            return (free_command_list(head), NULL);
        if (!head)
        {
            head = new_cmd;
            tail = new_cmd;
        }
        else
        {
            tail->next = new_cmd;
            tail = new_cmd;
        }
        if (*token_ptr && (*token_ptr)->type == TOKEN_PIPE)
            *token_ptr = (*token_ptr)->next;
    }
    return (head);
}

t_cmd   *parse_tokens(t_token *tokens)
{
    if (!validate_syntax(tokens))
        return (NULL);
    return (parse_pipeline(&tokens));
}