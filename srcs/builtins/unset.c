/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:01:32 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:01:38 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **args, t_env **env)
{
	int		i;
	int		exit_status;

	i = 1;
	exit_status = 0;
	if (!args || !args[1] || !env || !*env)
		return (exit_status);
	while (args[i])
	{
		if (!exit_status && !ft_is_valid_identifier(args[i]))
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
