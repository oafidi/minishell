#include "../../includes/minishell.h"

static void    fill_word(char *result, char **input, int len, int *should_expand)
{
    int     i;
    int     j;
    char    quote;

    i = 0;
    j = 0;
    quote = 0;
    while (i < len)
    {
        if (is_quote((*input)[i]) && quote == 0)
        {
            quote = (*input)[i];
            if ((*input)[i] == '\'')
                *should_expand = 0;
            i++;
        }
        else if ((*input)[i] == quote)
        {
            quote = 0;
            i++;
        }
        else
            result[j++] = (*input)[i++];
    }
}

static char    *extract_word(char **input, int *should_expand)
{
    char    *result;
    int     len;

    len = get_word_length(*input);
    if (len == 0)
        return NULL;
    result = malloc(len + 1);
    if (!result)
        return NULL;
    *should_expand = 1;
    fill_word(result, input, len, should_expand);
    result[len] = '\0';
    *input += len;
    return result;
}

static t_token *handle_operator(char **input)
{
	if (**input == '|')
		return ((*input)++, create_token(NULL, TOKEN_PIPE, 0));
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
			return ((*input)++, create_token(NULL, TOKEN_HEREDOC, 0));
		return (create_token(NULL, TOKEN_REDIR_IN, 0));
	}
	if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
			return ((*input)++, create_token(NULL, TOKEN_APPEND, 0));
		return (create_token(NULL, TOKEN_REDIR_OUT, 0));
	}
	return (NULL);
}

static t_token	*handle_word(char **input)
{
	char	*word;
	int		should_expand;

	word = extract_word(input, &should_expand);
	if (!word)
		return (NULL);
	return (create_token(word, TOKEN_WORD, should_expand));
}

t_token *lexer(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new_token;

    head = NULL;
    tail = NULL;
    if (!input || !check_quotes_balance(input))
        return (NULL);
    while (*input)
    {
        while (is_space(*input))
            input++;
        if (!*input)
            break;
        new_token = handle_operator(&input);
		if (!new_token)
			new_token = handle_word(&input);
		if (!new_token)
			return (free_token_list(head), NULL);
		add_token_to_list(&head, &tail, new_token);
    }
	new_token = create_token(NULL, TOKEN_END, 0);
	add_token_to_list(&head, &tail, new_token);
	return (head);
}
