/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:42:46 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/03 03:42:48 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd   *create_command(void)
{
    t_cmd   *cmd;
    
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->line = NULL;
    cmd->argc = 0;
    cmd->args = NULL;
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
    redir->fd = -1;
    redir->ambiguous_flag = 0;
    redir->should_expand = 1;
    if (!redir->target)
    {
        free(redir);
        return (NULL);
    }
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

static int count_command_args(t_token *start)
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

t_cmd	*init_command_parsing(t_token *token)
{
	t_cmd	*cmd;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	cmd->argc = count_command_args(token);
	cmd->args = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	return (cmd);
}
