/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:55:14 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/30 18:55:14 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	get_signal(void)
{
	return (g_signal);
}

void	reset_signal(void)
{
	g_signal = 0;
}

static void	handle_sigint(int sig)
{
	ssize_t re;

	(void)sig;
	g_signal = 130;
	re = write(1, "\n", 1);
	(void)re;
	rl_replace_line("", 0); //limpa linha atual
	rl_on_new_line(); //nova linha lógica
	rl_redisplay(); //redefine o prompt
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}