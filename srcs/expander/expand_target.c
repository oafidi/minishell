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

static char macro_to_char(int macro)
{
	if (macro == SINGLE_QUOTE)
		return '\'';
	else if (macro == DOUBLE_QUOTE)
		return '"';
	return 0;
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
			if (target[i] != macro_to_char(quote_state) && quote_state != NO_QUOTE)
				result = ft_strjoin_char(result, target[i], 0);
			update_quote_state(target[i], &quote_state);
			i++;
		}
		else if (target[i] == '$' && quote_state != SINGLE_QUOTE)
		{
			var_expansion = expand_variable(target, &i, global_struct->env,
											global_struct->last_exit_status);
			printf("Variable expansion: %s\n", var_expansion);
			if (var_expansion)
			{
				if (quote_state == NO_QUOTE && count_words(var_expansion) != 1){
					redir->ambiguous_flag = 1;
					printf("Ambiguous redirection: %s\n", var_expansion);
				}
				result = ft_strjoin(result, var_expansion, 0);
				printf("Expanded result: %s\n", result);
				free(var_expansion);
			}
		}
		else
		{
			result = ft_strjoin_char(result, target[i], 0);
			i++;
		}
		if (!result)
			return (NULL);
	}
	printf("Final expanded result: %s\n", result);
	return (result);
}

void	expand_redir_target(t_redir *redir, global_struct *global_struct)
{
	char	*expanded;

	if (!redir || !redir->target || !global_struct)
		return ;
	expanded = expand_string(redir, redir->target, global_struct);
	if (!expanded)
	{
		redir->ambiguous_flag = 1;
		return ;
	}
	free(redir->target);
	redir->target = expanded;
}
