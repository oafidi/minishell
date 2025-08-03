/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:42:38 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/03 03:42:39 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_word_token(t_cmd *cmd, t_token **token_ptr)
{
	cmd->line = ft_strjoin(cmd->line, (*token_ptr)->value);
	return (cmd->line != NULL);
}

static int	parse_redirection_token(t_cmd *cmd, t_token **token_ptr)
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

static t_cmd	*parse_single_command(t_token **token_ptr)
{
	t_cmd	*cmd;

	cmd = init_command_parsing(*token_ptr);
	if (!cmd)
		return (NULL);
	while (*token_ptr && (*token_ptr)->type != TOKEN_PIPE
		&& (*token_ptr)->type != TOKEN_END)
	{
		if ((*token_ptr)->type == TOKEN_WORD)
		{
			if (!parse_word_token(cmd, token_ptr))
				return (free_command(cmd), NULL);
		}
		else if ((*token_ptr)->type >= TOKEN_REDIR_IN
			&& (*token_ptr)->type <= TOKEN_HEREDOC)
		{
			if (!parse_redirection_token(cmd, token_ptr))
				return (free_command(cmd), NULL);
		}
	}
	return (cmd);
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

t_cmd   *parser(t_token *tokens, global_struct *global_struct)
{
	t_cmd *head;

    if (!tokens || !validate_syntax(tokens, global_struct))
        return (NULL);
	head = parse_pipeline(&tokens);
    if (!head)
        return (NULL);
    return (expand_pipeline(head, global_struct));
}