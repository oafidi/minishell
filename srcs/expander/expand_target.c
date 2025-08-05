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

static char	*join_three(char start, char *s, char last)
{
    size_t	len = (s ? ft_strlen(s) : 0);
    char	*res;
    size_t	i = 0, j = 0;
    size_t	add = (start ? 1 : 0) + (last ? 1 : 0);

    res = malloc(len + add + 1);
    if (!res)
        return (NULL);
    if (start)
        res[i++] = start;
    if (s)
        while (s[j])
            res[i++] = s[j++];
    if (last)
        res[i++] = last;
    res[i] = '\0';
    return (res);
}

static int	count_words(char start, char *s, char last)
{
	int	count;
	char 	*temp;
	int i;

	i = 0;
	temp = join_three(start, s, last);
	if (!temp)
		return (0);
	count = 0;
	printf("Counting words in: %s\n", temp);
	while (temp[i])
	{
		while (is_space(temp[i]))
			i++;
		if (temp[i])
			count++;
		while (temp[i] && !is_space(temp[i]))
			i++;
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
	int last_index;
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
				last_index = ft_strlen(result) - 1;
				if (last_index < 0)
					last_index = 0;
				if (quote_state == NO_QUOTE && count_words(result[last_index],var_expansion, target[i]) != 1){
					printf("result: |%c|, var_expansion: |%s|, target[i]: |%c|\n", result[last_index], var_expansion, target[i]);
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
