/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:44:17 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/18 12:44:18 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_redirections(t_redir *redir, t_global_struct *global_struct)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (!process_heredoc_delimiter(current))
				return (0);
		}
		else
		{
			if (!expand_redir_target(current, global_struct))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

static char	**remove_quotes_from_args(char **args)
{
	int		i;
	char	*tmp;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		tmp = remove_quotes(args[i]);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
	return (args);
}

t_cmd	*expand_pipeline(t_cmd *head, t_global_struct *global_struct)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		if (!expand_redirections(current->redirs, global_struct))
			return (free_command_list(head), NULL);
		if (!expand_line(current, global_struct))
			return (free_command_list(head), NULL);
		current->args = remove_quotes_from_args(line_to_args(current->line));
		current = current->next;
	}
	return (head);
}
