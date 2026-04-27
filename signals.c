/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:55:14 by giodos-s          #+#    #+#             */
/*   Updated: 2026/04/27 18:55:14 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* 		Global Variable                                   */
/*      usage : The global variable used strictly for signal handling.        */
/* ************************************************************************** */
volatile int	g_signal = 0;

/* ************************************************************************** */
/*                        Signal state management:                            */
/* - get_signal: Retrieves the current value of the global signal variable.   */
/* - reset_signal: Clears the global signal variable by resetting it to zero. */
/* These functions encapsulate access to the global state, ensuring           */
/* synchronized tracking of user interruptions.                               */
/* ************************************************************************** */
int	get_signal(void)
{
	return (g_signal);
}

void	reset_signal(void)
{
	g_signal = 0;
}

/* ************************************************************************** */
/*                   Signal handler for SIGINT (Ctrl+C):                      */
/* 1. Updates global signal status to 130 (standard exit code for SIGINT).    */
/* 2. Writes a newline to move the cursor down.                               */
/* 3. Resets the readline internal state and buffer to display a clean        */
/* prompt on a new line without exiting the shell.                            */
/* ************************************************************************** */
static void	handle_sigint(int sig)
{
	ssize_t	re;

	(void)sig;
	g_signal = 130;
	re = write(1, "\n", 1);
	(void)re;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* ************************************************************************** */
/*             Configures signal handling for the interactive shell           */
/*    1. SIGINT (Ctrl+C): Redirects to a custom handler to reset the prompt.  */
/*    2. SIGQUIT (Ctrl+\): Set to SIG_IGN to be ignored by the shell,         */
/*    preventing unwanted exits or core dumps during input.                   */
/* ************************************************************************** */
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
