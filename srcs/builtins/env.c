/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:24:13 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/16 15:47:07 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->kv && ft_strchr(env->kv, '='))
			printf("%s\n", env->kv);
		env = env->next;
	}
}
