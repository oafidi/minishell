/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:01:47 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:01:49 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

static int	init_global_struct(t_global_struct *global_struct, char **env)
{
	global_struct->cmds = NULL;
	exit_status_set(0);
	global_struct->tokens = NULL;
	global_struct->env = copy_environment(env);
	if (!global_struct->env)
		return (ft_putstr_fd("Failed to copy environment!\n", 2), 0);
	return (1);
}

static char	*ft_readline(t_global_struct *global_struct)
{
	char	*input;

	input = readline("minishell-$ ");
	if (g_sig == 2)
		g_sig = 0;
	if (!input)
	{
		rl_clear_history();
		free_env_list(global_struct->env);
		ft_putstr_fd("exit\n", 2);
		exit(*exit_status_get());
	}
	else if (*input)
		add_history(input);
	return (input);
}

static int	minishell_loop(t_global_struct *global_struct)
{
	char			**heredoc;
	char			*input;

	store_terminal();
	while (1)
	{
		setup_signals();
		input = ft_readline(global_struct);
		global_struct->tokens = lexer(input);
		global_struct->cmds = parser(global_struct->tokens, global_struct);
		free(input);
		if (!global_struct->cmds)
		{
			free_token_list(global_struct->tokens);
			continue ;
		}
		heredoc = herdoc_init(global_struct->tokens);
		execute_command(global_struct->cmds, heredoc, \
			&global_struct->env, count_heredocs(global_struct->tokens));
		free_token_list(global_struct->tokens);
		free_command_list(global_struct->cmds);
	}
	return (free_env_list(global_struct->env), 1);
}

int	main(int argc, char **argv, char **env)
{
	t_global_struct	global_struct;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Invalid Arguments !\n", 2), 1);
	if (!isatty(0) || !isatty(1) || !init_global_struct(&global_struct, env))
		return (1);
	return (minishell_loop(&global_struct));
}
