/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:50:59 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/03 03:34:05 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// just for test 
const char *token_type_to_str(t_token_type type)
{
    if (type == TOKEN_WORD) return "WORD";
    if (type == TOKEN_PIPE) return "PIPE";
    if (type == TOKEN_REDIR_IN) return "REDIR_IN";
    if (type == TOKEN_REDIR_OUT) return "REDIR_OUT";
    if (type == TOKEN_APPEND) return "APPEND";
    if (type == TOKEN_HEREDOC) return "HEREDOC";
    if (type == TOKEN_END) return "END";
    return "UNKNOWN";
}

void print_token_list(t_token *head)
{
    int i = 0;
    while (head)
    {
        printf("Token %d: type = %-10s | value = \"%s\"\n", i,
            token_type_to_str(head->type),
            head->value ? head->value : "(null)");
        head = head->next;
        i++;
    }
}
// just for test end

int init_global_struct(global_struct *global_struct, char **env)
{
    global_struct->cmds = 0;
    global_struct->last_exit_status = 0;
    global_struct->tokens = 0;
    global_struct->env = copy_environment(env);
    if (!global_struct->env)
        return (ft_putstr_fd("Failed to copy environment!\n", 2), 0);
    return (1);
}

char    *ft_readline(global_struct *global_struct)
{
    char    *input;

    input = readline("minishell-$ ");
    if (!input)
    {
        rl_clear_history();
		free_environment(&global_struct->env);
		ft_putstr_fd("exit\n", 2);
		exit(global_struct->last_exit_status);
    }
    else
        add_history(input);
    return (input);
}

void    minishell_loop(char **env)
{
    global_struct   global_struct;
    char            *input;

    if (!init_global_struct(&global_struct, env))
        exit(1);
    while (1)
    {
        input = ft_readline(&global_struct);
        //printf("Input: %s\n", input);
        global_struct.tokens = lexer(input, &global_struct);
        //print_token_list(global_struct.tokens);
        global_struct.cmds = parser(global_struct.tokens, &global_struct);
        print_cmd_list(global_struct.cmds);
        free(input);
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argv;
    if (argc != 1)
        return (ft_putstr_fd("Invalid Arguments !\n", 2), 1);
    minishell_loop(env);
}
