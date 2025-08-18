/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:25:28 by yettalib          #+#    #+#             */
/*   Updated: 2025/08/18 13:51:44 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct termios	*terminal_settings(void)
{
	static struct termios	settings;

	return (&settings);
}

void	store_terminal(void)
{
	struct termios	*ts;

	ts = terminal_settings();
	tcgetattr(STDIN_FILENO, ts);
}

void	restore_terminal(void)
{
	struct termios	*ts;

	ts = terminal_settings();
	tcsetattr(STDIN_FILENO, TCSANOW, ts);
}
