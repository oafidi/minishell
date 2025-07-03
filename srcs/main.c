#include "../includes/minishell.h"

void print_redirs(t_redir *redir)
{
    while (redir)
    {
        printf("  REDIR type: %d, target: %s, heredoc_expand: %d\n",
               redir->type, redir->target, redir->heredoc_expand);
        redir = redir->next;
    }
}

void print_cmds(t_cmd *cmd)
{
    int i;
    int n = 1;
    while (cmd)
    {
        printf("=== Command %d ===\n", n++);
        for (i = 0; cmd->args && cmd->args[i]; i++)
            printf("  ARG[%d]: %s\n", i, cmd->args[i]);
        print_redirs(cmd->redirs);
        cmd = cmd->next;
    }
}

int main(void)
{
    char *input;
    t_token *tokens;
    t_cmd *cmds;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (*input)
            add_history(input);

        tokens = lexer(input);
        if (!tokens)
        {
            printf("Erreur de lexing.\n");
            free(input);
            continue;
        }
        cmds = parse_tokens(tokens);
        if (!cmds)
        {
            printf("Erreur de parsing.\n");
            free_token_list(tokens);
            free(input);
            continue;
        }
        print_cmds(cmds);
        free_command_list(cmds);
        free_token_list(tokens);
        free(input);
    }
    return 0;
}