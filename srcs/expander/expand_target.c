/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_target.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:42:06 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/03 03:42:08 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s)
			count++;
		else
			return (1);
		while (*s && !is_space(*s))
			s++;
	}
	return (count);
}

static char	*expand_string(t_redir *redir, char *target, global_struct *global_struct)
{
	char	*result;
	char	*var_expansion;
	int		i;
	int		quote_state;

	if (!target)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	quote_state = NO_QUOTE;
	while (target[i])
	{
		if ((target[i] == '\'' || target[i] == '"'))
		{
			if (target[i] != quote_state && quote_state != NO_QUOTE)
				result = ft_strjoin(result, target + i);
			update_quote_state(target[i], &quote_state);
			i++;
		}
		else if (target[i] == '$' && quote_state != SINGLE_QUOTE)
		{
			var_expansion = expand_variable(target, &i, global_struct->env,
											global_struct->last_exit_status);
			if (var_expansion)
			{
				if (quote_state != DOUBLE_QUOTE && count_words(var_expansion) != 1)
					redir->ambiguous_flag = 1;
				result = ft_strjoin(result, var_expansion);
				free(var_expansion);
			}
		}
		else
		{
			result = ft_strjoin(result, target + i);
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

void	expand_redir_target(t_redir *redir, global_struct *global_struct)
{
	char	*expanded;
	int		word_count;

	if (!redir || !redir->target || !global_struct)
		return ;
	expanded = expand_string(redir, redir->target, global_struct);
	if (!expanded)
	{
		redir->ambiguous_flag = 1;
		return ;
	}
	word_count = count_words(expanded);
	if (word_count != 1)
		return (redir->ambiguous_flag = 1, free(expanded));
	free(redir->target);
	redir->target = expanded;
}
