/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:35:35 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/13 17:16:58 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atoi_long(const char *str, int *overflow)
{
	int		sign;
	long	result;

	*overflow = 0;
	result = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	while (*str && ft_isdigit(*str))
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static char	*skip_spaces(char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	return (s);
}

static char	*trim_arg(char *arg)
{
	char	*start;
	char	*end;

	start = skip_spaces(arg);
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || (*end >= 9 && *end <= 13)))
		end--;
	*(end + 1) = '\0';
	return (start);
}

int	ft_exit(char **args, int must_exit_)
{
	long	code;
	int		overflow;
	char	*start;

	if (must_exit_ && (isatty(0) && isatty(1)))
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args || !args[1])
		exit(0);
	start = trim_arg(args[1]);
	code = ft_atoi_long(start, &overflow);
	if (!is_numeric(start) || overflow)
	{
		write(2, "minishell: exit: ", 18);
		write(2, start, ft_strlen(start));
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	if (args[2])
		return (write(2, "minishell: exit: too many arguments\n", 36), 1);
	exit((unsigned char)code);
}
