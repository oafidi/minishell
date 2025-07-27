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
        expand_line(current->line, global_struct);
        current = current->next;
    }
}
