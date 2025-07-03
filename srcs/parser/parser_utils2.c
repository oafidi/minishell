#include "../../includes/minishell.h"

t_cmd	*init_command_parsing(t_token *token)
{
	t_cmd	*cmd;
    int		arg_count;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	arg_count = count_command_args(token);
	if (arg_count == 0)
		return (free(cmd), NULL);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	return (cmd);
}

int	parse_word_token(t_cmd *cmd, t_token **token_ptr, int *i)
{
	cmd->args[*i] = ft_strdup((*token_ptr)->value);
	if (!cmd->args[*i])
	{
		while (--(*i) >= 0)
			free(cmd->args[*i]);
		return (0);
	}
	(*i)++;
	*token_ptr = (*token_ptr)->next;
	return (1);
}

int	parse_redirection_token(t_cmd *cmd, t_token **token_ptr)
{
	t_redir			*redir;
	t_token_type	redir_type;

	redir_type = (*token_ptr)->type;
	*token_ptr = (*token_ptr)->next;
	redir = create_redirection(redir_type, (*token_ptr)->value);
	if (!redir)
		return (0);
	if (redir_type == TOKEN_HEREDOC)
		redir->heredoc_expand = (*token_ptr)->should_expand;
	add_redirection_to_cmd(cmd, redir);
	*token_ptr = (*token_ptr)->next;
	return (1);
}
