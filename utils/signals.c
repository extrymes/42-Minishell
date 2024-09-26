/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:06:19 by sabras            #+#    #+#             */
/*   Updated: 2024/09/26 08:19:28 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

static void	sigint_handler(int sig);
static void	sigint_handler_in_process(int sig);
static void	sigquit_handler_in_process(int sig);

void	handle_signals(int in_process)
{
	if (in_process)
	{
		signal(SIGINT, sigint_handler_in_process);
		signal(SIGQUIT, sigquit_handler_in_process);
	}
	else
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
}

void	reset_signal_status(void)
{
	rl_done = 0;
	g_signal_received = 0;
}

static void	sigint_handler(int sig)
{
	(void) sig;
	rl_done = 1;
	g_signal_received = sig;
}

static void	sigint_handler_in_process(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 2);
	rl_done = 1;
	g_signal_received = sig;
}

static void	sigquit_handler_in_process(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: (core dumped)\n", 2);
	g_signal_received = sig;
}
