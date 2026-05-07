/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:22:56 by giodos-s          #+#    #+#             */
/*   Updated: 2026/03/30 19:22:56 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* ************************************************************************** */
//*                          Path = /SRC/EXECUTION                            */
/*         - Function declarations and their respective .c files -            */
/* ************************************************************************** */
// * signals.c

int		get_signal(void);
void	reset_signal(void);
void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);

#endif
