#include "../../includes/minishell.h"


static int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*current;

	if (!env_list || !key)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*extract_var_name(char *str, int *len)
{
	char	*var_name;
	int		i;

	*len = 0;
	if (!str || !is_valid_var_start(str[0]))
		return (NULL);
	while (str[*len] && is_valid_var_char(str[*len]))
		(*len)++;
	var_name = malloc(sizeof(char) * (*len + 1));
	if (!var_name)
		return (NULL);
	i = -1;
	while (++i < *len)
		var_name[i] = str[i];
	var_name[i] = '\0';
	return (var_name);
}

static char	*handle_exit_status(int *i, int exit_status)
{
	char	*result;

	*i += 2;
	result = ft_itoa(exit_status);
	return (result);
}

static char	*handle_invalid_var(int *i)
{
	char	*result;

	result = malloc(2);
	if (result)
	{
		result[0] = '$';
		result[1] = '\0';
	}
	(*i)++;
	return (result);
}

static char	*expand_variable(char *str, int *i, t_env *env_list, int exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	int		var_len;

	if (str[*i + 1] == '?')
		return (handle_exit_status(i, exit_status));
	var_name = extract_var_name(str + *i + 1, &var_len);
	if (!var_name)
		return (handle_invalid_var(i));
	*i += var_len + 1;
	var_value = get_env_value(env_list, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	result = ft_strdup(var_value);
	return (result);
}

static char	*append_char(char *str, char c)
{
	char	*result;
	int		len;
	int		i;

	len = 0;
	if (str)
		len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = str[i];
	result[i] = c;
	result[i + 1] = '\0';
	if (str)
		free(str);
	return (result);
}

static char	*append_string(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;
	int		j;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	j = -1;
	while (++j < len2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	if (s1)
		free(s1);
	return (result);
}

static void	update_quote_state(char c, int *quote_state)
{
	if (c == '\'' && *quote_state != DOUBLE_QUOTE)
	{
		if (*quote_state == SINGLE_QUOTE)
			*quote_state = NO_QUOTE;
		else
			*quote_state = SINGLE_QUOTE;
	}
	else if (c == '"' && *quote_state != SINGLE_QUOTE)
	{
		if (*quote_state == DOUBLE_QUOTE)
			*quote_state = NO_QUOTE;
		else
			*quote_state = DOUBLE_QUOTE;
	}
}

static char	*expand_string(char *target, global_struct *global_struct)
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
			update_quote_state(target[i], &quote_state);
			i++;
		}
		else if (target[i] == '$' && quote_state != SINGLE_QUOTE)
		{
			var_expansion = expand_variable(target, &i, global_struct->env_list,
											global_struct->exit_status);
			if (var_expansion)
			{
				result = append_string(result, var_expansion);
				free(var_expansion);
			}
		}
		else
		{
			result = append_char(result, target[i]);
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	count_words(char *str)
{
	int	count;
	int	i;
	int	in_word;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	in_word = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
		{
			if (in_word)
			{
				count++;
				in_word = 0;
			}
		}
		else if (!in_word)
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

static char	*get_first_word(char *str)
{
	int		start;
	int		end;
	int		i;
	char	*word;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (!str[i])
		return (ft_strdup(""));
	start = i;
	while (str[i] && !is_whitespace(str[i]))
		i++;
	end = i;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < (end - start))
		word[i] = str[start + i];
	word[i] = '\0';
	return (word);
}

void	expand_redir_target(t_redir *redir, global_struct *global_struct)
{
	char	*expanded;
	char	*final_target;
	int		word_count;

	if (!redir || !redir->target || !global_struct)
		return ;
	expanded = expand_string(redir->target, global_struct);
	if (!expanded)
	{
		redir->ambiguous_flag = 1;
		return ;
	}
	word_count = count_words(expanded);
	if (word_count != 1)
	{
		redir->ambiguous_flag = 1;
		free(expanded);
		return ;
	}
	final_target = get_first_word(expanded);
	free(expanded);
	if (!final_target || ft_strlen(final_target) == 0)
	{
		redir->ambiguous_flag = 1;
		if (final_target)
			free(final_target);
		return ;
	}
	free(redir->target);
	redir->target = final_target;
	redir->ambiguous_flag = 0;
}