/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:01:40 by oafidi            #+#    #+#             */
/*   Updated: 2025/08/18 17:01:45 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	result;

	if (!args[1])
		return (print_sorted_env(*env));
	result = 0;
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env))
			result = 1;
		i++;
	}
	return (result);
}
