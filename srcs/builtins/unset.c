/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:38:06 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/10 15:05:34 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(char *arg)
{
	int	i;

	if (!is_valid_var_start(arg[0]))
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!is_valid_var_char(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args || !args[1] || !env || !*env)
		return (exit_status);
	while (args[i])
	{
		if (!exit_status && !is_valid_identifier(args[i]))
		{
			exit_status = 1;
			ft_putstr_fd("minishell: unset: `", 2);
    		ft_putstr_fd(args[i], 2);
    		ft_putstr_fd("': not a valid identifier\n", 2);
			continue ;
		}
		delete_env_variable(args[i], env);
		i++;
	}
	return (exit_status);
}
