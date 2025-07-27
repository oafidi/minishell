#include "../../includes/minishell.h"

void	process_heredoc_delimiter(t_redir *redir)
{
	char	*clean_delimiter;

	if (check_quotes_type(redir->target) != NO_QUOTE)
		redir->should_expand = 0;
	clean_delimiter = remove_quotes(redir->target);
	if (!clean_delimiter)
		return ;
	free(redir->target);
	redir->target = clean_delimiter;
}
