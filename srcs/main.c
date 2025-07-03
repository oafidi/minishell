#include "../includes/minishell.h"

void print_tokens(t_token *head)
{
    while (head)
    {
        if (head->type == TOKEN_WORD)
            printf("WORD: %s (should_expand: %d)\n", head->value, head->should_expand);
        else if (head->type == TOKEN_PIPE)
            printf("PIPE (should_expand: %d)\n", head->should_expand);
        else if (head->type == TOKEN_REDIR_IN)
            printf("REDIR_IN (should_expand: %d)\n", head->should_expand);
        else if (head->type == TOKEN_REDIR_OUT)
            printf("REDIR_OUT (should_expand: %d)\n", head->should_expand);
        else if (head->type == TOKEN_HEREDOC)
            printf("HEREDOC (should_expand: %d)\n", head->should_expand);
        else if (head->type == TOKEN_APPEND)
            printf("APPEND (should_expand: %d)\n", head->should_expand);
        else if (head->type == TOKEN_END)
            printf("END (should_expand: %d)\n", head->should_expand);
        head = head->next;
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;

    char *input;
    t_token *tokens;

    while (1)
    {
        input = readline("Enter a command: ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        tokens = lexer(input);
        if (tokens)
        {
            print_tokens(tokens);
            free_token_list(tokens);
        }
        else
        {
            printf("Erreur de parsing ou quotes non fermées.\n");
        }
        free(input);
    }
    return 0;
}
