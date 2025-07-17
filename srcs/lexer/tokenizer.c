#include "../../includes/minishell.h"

static void    fill_word(char *result, char **input, int len)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (i < len)
        result[j++] = (*input)[i++];
    result[j] = 0;
}

static char    *extract_word(char **input)
{
    char    *result;
    int     len;

    len = get_word_length(*input);
    if (len == 0)
        return NULL;
    result = malloc(len + 1);
    if (!result)
        return NULL;
    fill_word(result, input, len);
    *input += len;
    return (result);
}

static t_token *handle_operator(char **input)
{
	if (**input == '|')
		return ((*input)++, create_token(NULL, TOKEN_PIPE));
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
			return ((*input)++, create_token(NULL, TOKEN_HEREDOC));
		return (create_token(NULL, TOKEN_REDIR_IN));
	}
	if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
			return ((*input)++, create_token(NULL, TOKEN_APPEND));
		return (create_token(NULL, TOKEN_REDIR_OUT));
	}
	return (NULL);
}

static t_token	*handle_word(char **input)
{
	char	*word;

	word = extract_word(input);
	if (!word)
		return (NULL);
	return (create_token(word, TOKEN_WORD));
}

t_token *lexer(char *input, global_struct *global_struct)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new_token;

    head = NULL;
    tail = NULL;
    if (!input || !check_quotes_balance(input))
        return (global_struct->last_exit_status = 1, NULL);
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
	new_token = create_token(NULL, TOKEN_END);
	add_token_to_list(&head, &tail, new_token);
	return (head);
}
