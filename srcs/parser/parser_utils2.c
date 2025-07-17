#include "../../includes/minishell.h"

t_cmd	*init_command_parsing(t_token *token)
{
	t_cmd	*cmd;
    int		arg_count;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	cmd->argc = count_command_args(token);
	cmd->args = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	return (cmd);
}

int	parse_word_token(t_cmd *cmd, t_token **token_ptr)
{
	cmd->line = ft_strjoin(cmd->line, (*token_ptr)->value);
	return (cmd->line != NULL);
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
	add_redirection_to_cmd(cmd, redir);
	*token_ptr = (*token_ptr)->next;
	return (1);
}