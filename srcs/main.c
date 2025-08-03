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
		free(global_struct);
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
        global_struct.tokens = lexer(input, &global_struct);
        global_struct.cmds = parser(global_struct.tokens, &global_struct);
        free(input);
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argv;
    if (argc != 1)
        return (ft_putstr_fd("Invalid Arguments !", 2), 1);
    minishell_loop(env);
}
