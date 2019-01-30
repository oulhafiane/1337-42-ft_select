/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:30:47 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/01/30 15:53:17 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	init_termios(struct termios *term)
{
	struct termios	cpy;

	//to verify fd 0 is good or not
	if (tcgetattr(0, term) == -1)
		return (-1);
	cpy = *term;
	cpy.c_lflag &= ~(ICANON);
	cpy.c_lflag &= ~(ECHO);
	cpy.c_cc[VMIN] = 1;
	cpy.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &cpy) == -1)
		return (-1);
	return (1);
}

void		exit_handler(int sig)
{
	if (sig == SIGCONT)
	{
		terms_handler(0);
		draw_args(1);
	}
	else
	{
		terms_handler(1);
		if (sig == SIGTSTP)
		{
			signal(SIGTSTP, SIG_DFL);
			ioctl(0, TIOCSTI, "\x1A");
		}
		if (sig != SIGTSTP)
			exit(-1);
	}
}

static void	set_signal_handlers(void)
{
	/*	signal(SIGHUP, &exit_handler);
		signal(SIGINT, &exit_handler);
		signal(SIGKILL, &exit_handler);
		signal(SIGTERM, &exit_handler);
		signal(SIGSTOP, &exit_handler);
		signal(SIGTSTP, &exit_handler);
		signal(SIGQUIT, &exit_handler);
		signal(SIGILL, &exit_handler);
		signal(SIGABRT, &exit_handler);
		signal(SIGTRAP, &exit_handler);
		signal(SIGEMT, &exit_handler);
		signal(SIGFPE, &exit_handler);
		signal(SIGBUS, &exit_handler);
		signal(SIGSEGV, &exit_handler);
		signal(SIGSYS, &exit_handler);
		signal(SIGTTIN, &exit_handler);
		signal(SIGTTOU, &exit_handler);
		signal(SIGXCPU, &exit_handler);
		signal(SIGXFSZ, &exit_handler);
		signal(SIGVTALRM, &exit_handler);
		signal(SIGALRM, &exit_handler);
		signal(SIGPROF, &exit_handler);*/
	signal(SIGTSTP, &exit_handler);
	signal(SIGCONT, &exit_handler);
	signal(SIGWINCH, &draw_args);
}

int			init_terms(void)
{
	char	*term_type;
	int		success;

	term_type = getenv("TERM");
	if (term_type == 0)
	{
		ft_printf_fd(2, "Cannot get terminal type from environement $TERM.\n");
		return (-1);
	}
	success = tgetent(NULL, term_type);
	if (success < 0)
	{
		ft_printf_fd(2, "Could not access the termcap data base.\n");
		return (-1);
	}
	else if (success == 0)
	{
		ft_printf_fd(2, "Terminal type %s is not defined.\n", term_type);
		return (-1);
	}
	set_signal_handlers();
	return (1);
}

int			terms_handler(int restore)
{
	static struct termios	term;

	if (restore == 0)
	{
		if (init_terms() == -1)
			return (-1);
		if (init_termios(&term) == -1)
			return (-1);
		tputs(tgoto(tgetstr("ti", NULL), 0, 0), 1, my_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("te", NULL), 0, 0), 1, my_putchar);
		if (tcsetattr(0, TCSADRAIN, &term) == -1)
			return (-1);
	}
	return (1);
}
