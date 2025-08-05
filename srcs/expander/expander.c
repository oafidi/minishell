/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:42:11 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/03 03:42:13 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_redirections(t_redir *redir, global_struct *global_struct)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
			process_heredoc_delimiter(current);
		else
			expand_redir_target(current, global_struct);
		current = current->next;
	}
}

t_cmd   *expand_pipeline(t_cmd *head, global_struct *global_struct)
{
    t_cmd *current;

    current = head;
    while (current)
    {
        expand_redirections(current->redirs, global_struct);
        expand_line(current, global_struct);
        current = current->next;
    }
	return (head);
}
